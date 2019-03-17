#include <sys/param.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <ft_ls.h>

unsigned short g_flag;

t_files_attrib *get_attr_from_path(char *path, int need_to_exclude_system)
{
	t_files_attrib *current_files_list;
	t_files_attrib *tmp_pre;
	t_files_attrib *first;
	DIR *dir;
	struct dirent *direntp;

	first = NULL;
	dir = opendir(path);
	if (errno == ENOENT)
	{
		errno = 0;
		return (NULL);
	}
	if ((direntp = readdir(dir)) != NULL)
	{
		current_files_list = ft_list_create(direntp->d_name, NULL, NULL);
		first = current_files_list;
		while (NULL != (direntp = readdir(dir)))
		{
			if ((need_to_exclude_system && direntp->d_name[0] != '.') ||
				!need_to_exclude_system)
			{
				tmp_pre = current_files_list;
				current_files_list = ft_list_create(direntp->d_name, NULL,
													NULL);
				ft_list_push(current_files_list, tmp_pre);
			}
		}
	}
	closedir(dir);
	return (first);
}

void get_path_list(t_props *curent)
{
	t_path *current_path;
	t_path *holder;

	g_flag = curent->flag;
	if (!curent->path)
		return;
	current_path = curent->path;
	holder = current_path;
	while ((current_path))
	{
		current_path->attrib = create_atr(
				"."); //todo restruct creating of . file
		ft_open_folder(current_path->path);
		current_path = current_path->next;
	}
	curent->path = holder;
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


	modeval = ft_memalloc(sizeof(char) * 9 + 2);
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

void get_long_format_props(t_files_attrib *atr)
{
	struct passwd *pasw;
	struct stat structstat;
	struct group *g;
	size_t len;
	char *path;

	path = atr->full_path;
	errno = 0;
	if (stat(path, &structstat) == -1)
	{
		//if (errno)
		//print_error(path, errno);
		return;
	}
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
	lstat(path, &structstat);
	len = (size_t) structstat.st_size + 1;
	if (S_ISLNK(structstat.st_mode))
	{
		atr->is_link = true;
		atr->st_mode_to_char[0] = 'l';
	}
	atr->link_pointer = ft_strnew(len);
	errno = 0;

	if (atr->is_link)
	{
		readlink(path, atr->link_pointer, len);
		atr->link_pointer[len - 1] = 0;
	}
}


static t_files_attrib *
ft_relink(t_files_attrib *root_file, char *name, char *full)
{
	if (!root_file)
		root_file = create_atr(name);
	else
	{
		root_file->next = create_atr(name);    //make next file
		root_file->next->previous = root_file;
	} //relink
	if (root_file->root)
		root_file->next->root = root_file->root;
	if (root_file->next)
		root_file = root_file->next;
	root_file->full_path = full;
	if (g_flag & L && (g_flag & A)) //todo .. managment
		get_long_format_props(root_file);
	return root_file;
}

char *get_full_path(char *fld_name, char *name)
{
	char *path;
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
	attrib = NULL;
	holder = NULL;
	errno = 0;
	if (!(dir = opendir(fld_name)))
	{
		//if (errno)
		//print_error(fld_name, errno, root_file);
		return;
	}
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
	}
	attrib = holder;
	print_level(attrib);
	if (g_flag & R_BIG)
	{
		while (attrib->next)
		{
			if (is_dir(attrib->full_path) &&
				!(ft_strequ(attrib->filename, ".") ||
				  ft_strequ(attrib->filename, "..")))
			{
				ft_open_folder(attrib->full_path);
			}
			free(attrib->previous);
			//todo make freeing great again
			attrib = attrib->next;
		}
	}
	closedir(dir);

}
