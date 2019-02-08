
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
t_files_list *read_path(char *path, int need_to_exclude_system);
t_files_list *ft_list_create(char *name, t_files_list *next, t_files_list
*prev);
t_files_list	*ft_list_insert(t_files_list *current, t_files_list *next,
								t_files_list *prev);
t_files_list	*ft_list_add_head(t_files_list *current,t_files_list *next);
t_files_list	*ft_list_add_tail(t_files_list *current, t_files_list *prev);

void	ft_free_chain(t_files_list *head);
#endif
