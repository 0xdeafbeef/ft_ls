#include <sys/param.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <ft_ls.h>

unsigned short g_flag;


void get_path_list(t_props *current)
{
	t_path *current_path;

	g_flag = current->flag;
	if (!current->path)
		return;
	current_path = current->path;
	while ((current_path))
	{
		ft_open_folder(current_path->path);
		current_path = current_path->next;
	}
}

/*
b     Block special file.
c     Character special file.
d     Directory.
l     Symbolic link.
s     Socket link.
p     FIFO.
-     Regular file.*/
//define S_IFIFO 0x1000  /* fifo */
//#define S_IFCHR 0x2000  /* character special */
//#define S_IFDIR 0x4000  /* directory */
//#define S_IFBLK 0x6000  /* block special */
//#define S_IFREG 0x8000  /* regular */
//#define S_IFLNK 0xA000  /* symbolic link  */
//#define S_IFNAM 0x5000  /* special named file */
void get_permissions(mode_t perm, t_files_attrib *attrib)
{
	char *modeval;


	modeval = ft_strnew(10);
	if (S_ISREG(perm))
		modeval[0] = '-';
	if (S_ISBLK(perm))
		modeval[0] = 'b';
	if (S_ISCHR(perm))
		modeval[0] = 'c';
	if (S_ISFIFO(perm))
		modeval[0] = 'p';
	if (S_ISSOCK(perm))
		modeval[0] = 's';
	if (S_ISDIR(perm))
		modeval[0] = 'd';
	modeval[1] = (char) ((perm & S_IRUSR) ? 'r' : '-');
	modeval[2] = (char) ((perm & S_IWUSR) ? 'w' : '-');
	modeval[3] = (char) ((perm & S_IXUSR) ? 'x' : '-');
	modeval[4] = (char) ((perm & S_IRGRP) ? 'r' : '-');
	modeval[5] = (char) ((perm & S_IWGRP) ? 'w' : '-');
	modeval[6] = (char) ((perm & S_IXGRP) ? 'x' : '-');
	modeval[7] = (char) ((perm & S_IROTH) ? 'r' : '-');
	modeval[8] = (char) ((perm & S_IWOTH) ? 'w' : '-');
	modeval[9] = (char) ((perm & S_IXOTH) ? 'x' : '-');
	modeval[10] = '\0';
	attrib->st_mode_to_char = modeval;
}

void get_long_format_props(t_files_attrib **attr)
{
	struct passwd *pasw;
	struct stat structstat;
	struct group *g;
	size_t len;
	t_files_attrib *atr;

	atr = *attr;
	errno = 0;
	if (lstat(atr->full_path, &structstat) == -1)
	{
		if (errno)
			print_error(atr->full_path, errno, atr);
		return;
	}
	if (S_ISCHR(structstat.st_mode))
	{
		atr->major = major(structstat.st_rdev);
		atr->minor = minor(structstat.st_rdev);
	} else
		atr->block_size = structstat.st_blocks;
	atr->timestamp = ft_strnew(TIME_FORMAT_LEN);
	pasw = getpwuid(structstat.st_uid);
	atr->owner_name = pasw->pw_name;
	g = getgrgid(pasw->pw_gid);
	atr->group_name = g->gr_name;
	get_permissions(structstat.st_mode, atr);
	atr->link_count = structstat.st_nlink;
	atr->file_size = (size_t) structstat.st_size;
	strftime(atr->timestamp, TIME_FORMAT_LEN, "%b %d %R",
			 gmtime(&(structstat.st_ctime)));
	len = (size_t) structstat.st_size + 1;
	if (S_ISLNK(structstat.st_mode))
	{
		atr->st_mode_to_char[0] = 'l';
		atr->link_pointer = ft_strnew(len);
		errno = 0;
		readlink(atr->full_path, atr->link_pointer, len);
		if (errno)
			print_error(atr->full_path, errno, atr);
		atr->link_pointer[len - 1] = 0;
	}
}


static t_files_attrib *
ft_relink(t_files_attrib *attr, char *name, char *full)
{
	if (!attr)
		attr = create_atr(name);
	else
	{
		attr->next = create_atr(name);    //make next file
		attr->next->previous = attr;
	} //relink
	if (attr->next)
		attr = attr->next;
	attr->full_path = full;
	if (g_flag & L)
		get_long_format_props(&attr);
	return attr;
}

char *get_full_path(char *fld_name, char *name)
{
	char *path;
	if (ft_strequ(fld_name, "/"))
		return (ft_strjoin(fld_name, name));

	path = ft_strnew(ft_strlen(fld_name) + 1 + ft_strlen(name));
	ft_strcat(path, fld_name);
	ft_strcat(path, "/");
	ft_strcat(path, name);
	return path;
}

void ft_open_folder(char *fld_name)
{
	DIR *dir;
	struct dirent *dirp;
	t_files_attrib *attrib;
	t_files_attrib *holder;
	t_bool first_asign;

	first_asign = true;
	holder = NULL;
	attrib = NULL;
	errno = 0;
	if (!(dir = opendir(fld_name)))
	{
		if (errno)
		{
			print_error(fld_name, errno, NULL);
		}
		return;
	}
	errno = 0;
	while ((dirp = readdir(dir)))
	{
		if (!(g_flag & A && dirp->d_name[0] != '.') || g_flag & A)
		{
			attrib = ft_relink(attrib, dirp->d_name,
							   get_full_path(fld_name, dirp->d_name));
			if (first_asign)
			{
				holder = attrib;
				first_asign = false;
			}
		}
		if (errno)
		{
			print_error(fld_name, errno, attrib);
			errno = 0;
			continue;
		}
	}
	attrib = holder;
	ft_merge_sort(&attrib, comparator_lex);
	print_level(attrib, g_flag);
	if (g_flag & R_BIG)
	{
		while (attrib)
		{
			if (IS_OK && is_dir(attrib->full_path) && !attrib->error_message)
				ft_open_folder(attrib->full_path);
			attrib = attrib->next;
		}
	}
	closedir(dir);
}

