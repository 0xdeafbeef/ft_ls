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
# define FT_LS_FT_LS_H

# include "structures.h"
# include <stdio.h>
# include <dirent.h>
# include <sys/types.h>
# include "libft.h"
# include <sys/ioctl.h>
# include <time.h>
# include <errno.h>
# include <sys/stat.h>
# include <sys/param.h>
# include <libgen.h>
# include <pwd.h>
# include <grp.h>
# include <ft_ls.h>
# include <sys/types.h>
# include <sys/acl.h>
# include <sys/xattr.h>

# define L_2_CACHE_SIZE 262144 - 1
# define IS_OK !(ft_strequ(atr->filename,".")||ft_strequ(atr->filename,".."))
# define TIME_FORMAT_LEN 12
# define L 0x01
# define R_BIG 0x02
# define A 0x04
# define R_SMALL 0x08
# define T 0x10

typedef char		t_bool;
enum
{
	false, true
};
void					get_long_format_props(t_files_attrib **a,
						unsigned int b);
void					get_path_list(t_props *current);
t_path					*ft_path_append_horizontal(t_path *node, char *dat);
t_props					*get_t_size_and_flags(int argc, char **argv);
void					print_error(char const *l, int r, t_files_attrib *l);
int						is_dir(const char *path);
t_files_attrib			*create_atr(char *name);
void					ft_open_folder(char *fld_name, char l, t_props *l);
void					ft_merge_sort(t_files_attrib **head_ref,
						t_bool(*comp)(t_files_attrib *a, t_files_attrib *b));
t_bool					comparator_lex_inv_ch(char *a, char *b);
t_bool					comparator_lex_ch(char *a, char *b);
void					print_level(t_files_attrib *attrib, unsigned int lol,
						int a, t_props *kek);
int						*normal_listing(t_files_attrib *attrib, int rec_call);
void					ft_merge_sort_wrapper(unsigned short int flag,
						t_files_attrib **head_ref);
void					sort_path(t_path *path);
t_bool					comparator_time(t_files_attrib *a, t_files_attrib *b);
t_bool					comparator_time_inv(t_files_attrib *a,
						t_files_attrib *b);
void					ft_cat(char *copied, char **buf);
void					flush_buf(char **buf_ptr);
void					add_spaces(char **buf, int count,
						const char *concatenated);
void					print_columns(t_props *property, t_files_attrib *attr,
						int rec_call);
extern char				*g_buf_start;
extern char				*g_buf_end;
extern unsigned short	g_flag;
void					swap_path(t_path *path, t_path *path_2);
char					*parse_time(const char *time);
t_bool					comparator_lex(t_files_attrib *a, t_files_attrib
						*b);
t_bool					comparator_lex_inv(t_files_attrib *a, t_files_attrib
						*b);
void					permissions_to_char(mode_t perm, char *modeval,
						char chr);
void					permisions_look_up(mode_t perm, char *modeval);
size_t					get_long_props_inner_getter(struct passwd *pasw,
						struct stat *structstat, struct group *g,
						t_files_attrib *atr);
void					get_permissions(mode_t perm, t_files_attrib *attrib);
void					link_parse(size_t len, t_files_attrib *atr);
void					majors_and_size_parse(struct stat *structstat,
						t_files_attrib *atr);
void					ft_open_folder_recurision(t_props *props, DIR *dir,
						t_files_attrib *atr);
char					*get_full_path(char *fld_name, char *name);
void					assign_all(t_props **props, t_path **pat,
						t_path **p_handler,
						t_bool *is_first_asign);
char					*concat_full_path(t_files_attrib *attrib, char **buf);
int						*calc_column_props(t_props *property,
						t_files_attrib *attr, int *prop, t_column *col);
void					calc_vertical_height(int *prop, t_column *col);
int						*get_longest_word(t_files_attrib *atr);
unsigned char			numlen(unsigned long long int num);
blkcnt_t				get_print_props_inner_lookup(t_files_attrib *attrib,
						t_print *print, blkcnt_t size);
char					*majors_and_size_format(t_files_attrib *attrib,
						t_print *print, char *itoa, char **buf);
void					long_listing_parser(t_print *print,
						t_files_attrib **attrib, char **buf);
void					print_concat_free(t_files_attrib **attrib,
						t_print *print, char **buf);
#endif
