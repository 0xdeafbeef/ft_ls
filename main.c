/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:47:13 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 21:44:59 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"



void get_path_list(t_props *curent)
{
	t_path *current_path;
	t_path *holder;
	t_bool flag;

	flag = !(curent->flag & A);
	if (!curent->path)
		return;
	current_path = curent->path;
	holder = current_path;
	current_path->attrib = get_attr_from_path(current_path->path, flag);
	while ((current_path = current_path->next))
		current_path->attrib = get_attr_from_path(current_path->path, flag);
	curent->path = holder;
}

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
int main(int argc, char **argv)
{
	t_props *props;
	t_path *pat;


	props = get_t_size_and_flags(argc, argv);
	get_path_list(props);
	pat = props->path;
	while (pat)
	{
		print_path_list(pat);
		pat = pat->next;
	}

	return 0;
}