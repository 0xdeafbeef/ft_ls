/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:56 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 20:47:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft/libft.h"
#include <sys/ioctl.h>
#include <time.h>

#ifndef FT_LS_FT_LS_H
# define FT_LS_FT_LS_H
# define NO_FLAGS 0x00
# define L 0x01
# define R_BIG 0x02
# define A 0x04
# define R_SMALL 0x08
# define T 0x10
# define IS_TERM 0x20
typedef int				t_bool;
enum { false, true };
typedef struct s_flags //todo remove cause deprecated
{
	t_bool no_flags;
	t_bool l;
	t_bool r_big;
	t_bool a;
	t_bool r_small;
	t_bool t;
	t_bool is_terminal;
}						t_flags;
typedef struct s_files_attrib
{
	struct s_files_attrib *next;
	struct s_files_attrib *previous;
	char *filename;
	size_t timestamp;
}							t_files_attrib;
typedef struct			s_path
{
	struct s_path		*next;
	char				*path;
	t_files_attrib		*attrib;

}						t_path;
typedef struct			s_props
{
	int					win_size; //todo implement this
	t_bool 				isterm;
	t_flags				*flags; //todo deprecated
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
void for_each_path(t_path *pat, void (*fun)(t_files_attrib *));
void						ft_free_chain(t_files_attrib *head);
void print_bits(unsigned short int c, char bytes);
#endif
