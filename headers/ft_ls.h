/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:56 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 18:48:59 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_FT_LS_H
 # define MALLOC_ERROR 3
# define FT_LS_FT_LS_H
#include "structures.h"
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include "libft.h"
#include <sys/ioctl.h>
#include <time.h>
#include <errno.h>
#include <sys/stat.h>
//#define ft_memalloc malloc

#define L_2_CACHE_SIZE 262144 - 1
# define IS_OK !(ft_strequ(attrib->filename,".")||ft_strequ(attrib->filename,".."))
# define TIME_FORMAT_LEN 12
# define L 0x01
# define R_BIG 0x02
# define A 0x04
# define R_SMALL 0x08
# define T 0x10
# define IS_TERM 0x20
typedef int					t_bool;
enum { false, true };
typedef struct 				s_files_attrib
{
	char 					*error_message;
	char					*full_path;
	char					*filename;
	struct s_files_attrib 	*next;
	struct s_files_attrib 	*previous;
	char *					timestamp;
	char*					st_mode_to_char;
	char					*owner_name;
	char					*group_name;
	size_t					file_size;
	int						link_count;
	blkcnt_t				block_size;
	char					*link_pointer;
	int						major;
	int						minor;
}							t_files_attrib;
typedef struct				s_path
{
	struct s_path			*next;
	char					*path;
	t_files_attrib			*attrib;
	}						t_path;
typedef struct				s_props
{
	int						win_size; //todo implement this
	t_bool 					isterm;
	unsigned short int		flag;
	t_path					*path;
}							t_props;

void						get_long_format_props(t_files_attrib **);
void						get_path_list(t_props *current);
t_path						*ft_path_append_horizontal(t_path *node,
														 char *dat);
t_props						*get_t_size_and_flags(int argc, char **argv);
void						print_bits(unsigned short int c, char bytes);
void						print_error(char const *, int, t_files_attrib*);
int							is_dir(const char *path);
void						ft_list_push_down(t_files_attrib *current,t_files_attrib *upper);

t_files_attrib				*create_atr(char *name);
void 						ft_open_folder(char *fld_name);
void						ft_merge_sort(t_files_attrib **head_ref, t_bool( *comp)(t_files_attrib *a,
		t_files_attrib *b));
t_bool						comparator_lex_inv(t_files_attrib *a,
												 t_files_attrib *b);
t_bool comparator_lex(t_files_attrib *a,t_files_attrib *b);
void print_level(t_files_attrib *attrib, unsigned int);

void ft_merge_sort_wrapper(unsigned short int flag, t_files_attrib **head_ref);
#endif
