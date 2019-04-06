#include <sys/param.h>
#include <libgen.h>
#include <pwd.h>
#include <grp.h>
#include <ft_ls.h>
#include <sys/types.h>
#include <sys/acl.h>
#include <sys/xattr.h>

unsigned short g_flag;


void get_path_list(t_props *current)
{
	t_path *current_path;
	t_bool assigment;

	assigment =0;
	g_flag = current->flag;
	if (!current->path)
		return;
	current_path = current->path;
	while ((current_path))
	{
		errno = 0;
		if(assigment)
		{
			ft_putstr(current_path->path);
			ft_putendl(":");
		}
		if (-1 == access(current_path->path, F_OK))
		{
			print_error(current_path->path, errno, NULL);
			current_path = current_path->next;
			continue;
		}
		ft_open_folder(current_path->path, 0);
		current_path = current_path->next;
		++assigment;
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
	acl_t acl;
	acl_entry_t dummy;
	ssize_t xattr;
	char chr;

	acl = NULL;
	xattr = 0;
	acl = acl_get_link_np(attrib->full_path, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = NULL;
	}
	xattr = listxattr(attrib->full_path, NULL, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
		xattr = 0;
	if (xattr > 0)
		chr = '@';
	else if (acl != NULL)
		chr = '+';
	else
		chr = ' ';
	acl_free(acl);
	modeval = ft_strnew(11);
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
	modeval[10] = chr;
	modeval[11] = '\0';
	attrib->st_mode_to_char = modeval;
}

char *parse_time(const char *time)
{
	char *ret;

	ret = ft_strnew(TIME_FORMAT_LEN);
	ft_strncpy(ret, time + 4, TIME_FORMAT_LEN);
	return (ret);
}

void get_long_format_props(t_files_attrib **attr, unsigned int flag)
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
	atr->time = structstat.st_ctime;
	if (flag & T && !(flag & L))
		return;
	atr->timestamp = parse_time(ctime(&structstat.st_ctime));
	if (S_ISCHR(structstat.st_mode))
	{
		atr->major = major(structstat.st_rdev);
		atr->minor = minor(structstat.st_rdev);
	} else
		atr->block_size = structstat.st_blocks;
	pasw = getpwuid(structstat.st_uid);
	atr->owner_name = pasw->pw_name;
	g = getgrgid(pasw->pw_gid);
	atr->group_name = g->gr_name;
	get_permissions(structstat.st_mode, atr);
	atr->link_count = structstat.st_nlink;
	atr->file_size = (size_t) structstat.st_size;
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
	if (g_flag & L || g_flag & T)
		get_long_format_props(&attr, g_flag);
	return attr;
}

char *get_full_path(char *fld_name, char *name)
{
	char *path;
	int len;

	len = ft_strlen(fld_name);
	path = ft_strnew(len + 1 + ft_strlen(name));
	ft_strcat(path, fld_name);
	if (fld_name[len - 1] != '/')
		ft_strcat(path, "/");
	ft_strcat(path, name);
	return path;
}

void ft_open_folder(char *fld_name, char rec_cal)
{
	DIR *dir;
	struct dirent *dirp;
	t_files_attrib *attrib;
	t_files_attrib *holder;
	char first_asign;
	struct stat structstat;

	first_asign = 1;
	attrib = NULL;
	holder = attrib;
	errno = 0;
	if (!(dir = opendir(fld_name)))
	{
		if (lstat(fld_name, &structstat) == 0)
		{
			attrib = ft_relink(attrib, fld_name, fld_name);
			if (errno && rec_cal)
			{
				print_error(fld_name, errno, NULL);
				return;
			}
			print_level(attrib,g_flag, rec_cal);
			free(attrib->filename);
			free(attrib);
		}
		return;
	}
	while ((dirp = readdir(dir)))
	{
		if (!(!(g_flag & A) && dirp->d_name[0] == '.') || g_flag & A)
		{
			attrib = ft_relink(attrib, dirp->d_name,
							   get_full_path(fld_name, dirp->d_name));
			if (first_asign)
			{
				holder = attrib;
				first_asign = 0;
			}
		}
	}
	attrib = holder;
	ft_merge_sort_wrapper(g_flag, &attrib);
	print_level(attrib, g_flag, rec_cal);
	if (g_flag & R_BIG)
	{
		while (attrib)
		{
			if (IS_OK && is_dir(attrib->full_path) && !attrib->error_message)
			{
				ft_open_folder(attrib->full_path, 1);
			}
			attrib = attrib->next;
		}
	}
	closedir(dir);
}

