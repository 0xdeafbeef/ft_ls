/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:56 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 21:34:14 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>

#ifndef FT_LS_FT_LS_H
# define FT_LS_FT_LS_H
# define NO_FLAGS 0
# define L 0x01
# define R_BIG 0x02
# define A 0x04
# define R_SMALL 0x08
# define T 0x10
# define IS_TERM 0x20
typedef int				t_bool;
enum { false, true };
typedef struct s_files_attrib
{
	struct s_files_attrib *next;
	struct s_files_attrib *previous;
	char *filename;
}							t_files_attrib;
typedef struct			s_path
{
	struct s_path		*next;
	char				*path;
	t_files_attrib		*attrib;
	time_t				timestamp;
	char				permissions;
	char				*owner_name;
	char				*group_name;
	size_t				file_size;
	size_t				link_count;
	t_bool				is_link;
	}						t_path;
typedef struct				s_link
{
	t_bool					is_soft_link;
	char					*link_pointer;
}							t_link;	
typedef struct			s_props
{
	int					win_size; //todo implement this
	t_bool 				isterm;
	unsigned short int	flag;
	t_path				*path;
}						t_props;

t_path						*ft_path_append(t_path *node, char *dat);
void						ft_free_path_chain(t_path *tail);
t_files_attrib				*get_attr_from_path(char *path,
												  int need_to_exclude_system);
t_files_attrib				*ft_list_create(char *name, t_files_attrib *next,
		t_files_attrib *prev);
t_files_attrib				*ft_list_insert(t_files_attrib *current,
		t_files_attrib *next, t_files_attrib *prev);
t_files_attrib				*ft_list_add_head(t_files_attrib *current,
		t_files_attrib *next);
t_files_attrib				*ft_list_push(t_files_attrib *current,
											t_files_attrib *prev);
void						for_each_path(t_path *pat, void (*fun)(t_files_attrib *));
void						ft_free_chain(t_files_attrib *head);
void						print_bits(unsigned short int c, char bytes);
void print_path_list(t_path *path);
void print_error(char const *error_file, char const *msg, int error_num);
#endif
