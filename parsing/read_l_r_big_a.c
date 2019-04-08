/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_l_R_a.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:34:18 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 16:37:12 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned short	g_flag;

void					get_long_format_props(t_files_attrib **attr,
						unsigned int flag)
{
	struct passwd		*pasw;
	struct stat			structstat;
	struct group		*g;
	size_t				len;
	t_files_attrib		*atr;

	atr = *attr;
	errno = 0;
	if (lstat(atr->full_path, &structstat) == -1)
	{
		if (errno)
			print_error(atr->full_path, errno, atr);
		return ;
	}
	atr->time = structstat.st_ctime;
	if (flag & T && !(flag & L))
		return ;
	atr->timestamp = parse_time(ctime(&structstat.st_ctime));
	majors_and_size_parse(&structstat, atr);
	len = get_long_props_inner_getter(pasw, &structstat, g, atr);
	if (S_ISLNK(structstat.st_mode))
		link_parse(len, atr);
}

t_files_attrib			*ft_relink(t_files_attrib *attr, char *name, char *ful)
{
	if (!attr)
		attr = create_atr(name);
	else
	{
		attr->next = create_atr(name);
		attr->next->previous = attr;
	}
	if (attr->next)
		attr = attr->next;
	attr->full_path = ful;
	if (g_flag & L || g_flag & T)
		get_long_format_props(&attr, g_flag);
	return (attr);
}

t_files_attrib			*read_inner_loop(char *fld_name, DIR *dir,
						struct dirent *dirp, t_files_attrib *attrib)
{
	t_files_attrib		*holder;
	char				first_assign;

	holder = NULL;
	dirp = NULL;
	first_assign = 1;
	while ((dirp = readdir(dir)))
	{
		if (!(!(g_flag & A) && dirp->d_name[0] == '.') || g_flag & A)
		{
			attrib = ft_relink(attrib, dirp->d_name,
					get_full_path(fld_name, dirp->d_name));
			if (first_assign)
			{
				holder = attrib;
				first_assign = 0;
			}
		}
	}
	return (holder);
}

void					ft_open_folder_recurision(t_props *props, DIR *dir,
						t_files_attrib *atr)
{
	if (g_flag & R_BIG)
	{
		while (atr)
		{
			if (IS_OK && is_dir(atr->full_path) && !atr->error_message)
			{
				ft_open_folder(atr->full_path, 1, props);
			}
			atr = atr->next;
		}
	}
	closedir(dir);
}

void					ft_open_folder(char *fld_name, char rec_cal,
						t_props *props)
{
	DIR					*dir;
	struct dirent		*dirp;
	t_files_attrib		*attrib;
	struct stat			structstat;

	attrib = NULL;
	errno = 0;
	if (!(dir = opendir(fld_name)))
	{
		if (lstat(fld_name, &structstat) == 0)
		{
			attrib = ft_relink(attrib, fld_name, fld_name);
			if (errno && rec_cal)
			{
				print_error(fld_name, errno, NULL);
				return ;
			}
			print_level(attrib, g_flag, rec_cal, props);
		}
		return ;
	}
	attrib = read_inner_loop(fld_name, dir, dirp, attrib);
	ft_merge_sort_wrapper(g_flag, &attrib);
	print_level(attrib, g_flag, rec_cal, props);
	ft_open_folder_recurision(props, dir, attrib);
}
