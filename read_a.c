#include <sys/param.h>
#include <libgen.h>
#include "ft_ls.h"

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
	t_bool flag;
	t_bool recurisive_traverse;

	recurisive_traverse = curent->flag & (unsigned int) R_BIG;
	g_flag = curent->flag;

	flag = !(curent->flag & A);
	if (!curent->path)
		return;
	current_path = curent->path;
	holder = current_path;
	while ((current_path))
	{
		current_path->attrib = create_atr(".");
		if (recurisive_traverse)
			ft_open_folder(current_path->path, current_path->attrib);
		else
			current_path->attrib = get_attr_from_path(current_path->path, flag);
		current_path = current_path->next;
	}
	curent->path = holder;
}
void						get_long_format_props(t_files_attrib *atr, const char *name)
{
	
}

static t_files_attrib *ft_relink(t_files_attrib *root_file, const char *name)
{
	root_file->next = create_atr(name);    //make next file
	root_file->next->previous = root_file; //relink
	if (root_file->root)
		root_file->next->root = root_file->root;
	root_file = root_file->next;
	if (g_flag & L)
		get_long_format_props(root_file, name);

	return root_file;
}

void ft_open_folder(char *fld_name, t_files_attrib *root_file)
{
	DIR *dir;
	struct dirent *dirp;
	char name[1024];
	errno = 0;
	if (!(dir = opendir(fld_name)))
	{
		if (errno)
//			print_error(errno); //todo add to error_list
			return;
	}
	while ((dirp = readdir(dir)))
	{
		name[ft_strlen(dirp->d_name)] = 0;
		ft_strcpy(name, dirp->d_name);
		if ((!(g_flag & A) && 0[name] != '.') || (g_flag & A))
		{
			if (dirp->d_type == DT_DIR && !(ft_strequ(name, ".") ||
											ft_strequ(name, "..")))
			{

				root_file = ft_relink(root_file, name);
				root_file->leaf = create_atr(".");
				root_file->leaf->root = root_file;
				ft_open_folder(ft_strjoin(ft_strjoin(fld_name, "/"), name),
							   root_file->leaf);
			} else if (!ft_strequ(name, "."))
				root_file = ft_relink(root_file, name);
		}
	}
	if (dir)
		closedir(dir);
}
