
#ifndef FT_LS_FT_LS_H
#define FT_LS_FT_LS_H

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include <sys/ioctl.h>
#include <time.h>
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

typedef	struct		s_files_attrib
{
	struct s_files_attrib *next;
	struct s_files_attrib *previous;
	char *filename;
	size_t timestamp;
}					t_files_attrib;
t_files_attrib *read_path(char *path, int need_to_exclude_system);
t_files_attrib *ft_list_create(char *name, t_files_attrib *next, t_files_attrib
*prev);
t_files_attrib	*ft_list_insert(t_files_attrib *current, t_files_attrib *next,
								t_files_attrib *prev);
t_files_attrib	*ft_list_add_head(t_files_attrib *current,t_files_attrib *next);
t_files_attrib	*ft_list_add_tail(t_files_attrib *current, t_files_attrib *prev);

void	ft_free_chain(t_files_attrib *head);
#endif
