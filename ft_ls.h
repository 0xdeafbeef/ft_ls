
#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include <sys/ioctl.h>

typedef struct		s_flags
{
	char noFlags;
	char l;
	char r_big;
	char a;
	char r_small;
	char t;
	char is_terminal;
}					t_flags;

typedef struct		s_props
{
	int win_size;
	t_flags *flags;
	char *path;
}					t_props;

typedef struct		s_folder_content
{
	DIR		*dir;
	char	*file_name;
}					t_folder_content;

typedef	struct		s_files_list
{
	struct s_files_list *next;
	struct s_files_list *previous;
	char *filename;
	DIR *dir;
}					t_files_list;

t_files_list *ft_list_create(char *name, t_files_list *next, t_files_list
*prev);
#endif
