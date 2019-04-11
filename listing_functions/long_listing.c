/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   long_listing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:20:52 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/09 00:22:36 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

char	*majors_and_size_format(t_files_attrib *attrib, t_print *print,
		char *itoa, char **buf)
{
	if (attrib->major)
	{
		print->has_major = 1;
		itoa = ft_itoa(attrib->major);
		add_spaces(buf, print->major_size, itoa);
		ft_cat(" ", buf);
		ft_cat(itoa, buf);
		ft_cat(",", buf);
		free(itoa);
		itoa = ft_itoa(attrib->minor);
		add_spaces(buf, print->file_size_max, itoa);
		ft_cat(itoa, buf);
		free(itoa);
	}
	else
	{
		itoa = ft_itoa_big(attrib->file_size);
		add_spaces(buf, print->major_size, "\0");
		ft_cat("  ", buf);
		add_spaces(buf, print->file_size_max, itoa);
		ft_cat(itoa, buf);
		free(itoa);
	}
	return (*buf);
}

void	long_listing_parser(t_print *print, t_files_attrib **attrib,
		char **buf)
{
	char	*itoa;

	ft_cat((*attrib)->st_mode_to_char, buf);
	ft_cat(" ", buf);
	free((*attrib)->st_mode_to_char);
	itoa = ft_itoa((*attrib)->link_count);
	add_spaces(buf, print->links_max, itoa);
	ft_cat(itoa, buf);
	free(itoa);
	ft_cat(" ", buf);
	ft_cat((*attrib)->owner_name, buf);
	add_spaces(buf, print->owner_len_max, (*attrib)->owner_name);
	free((*attrib)->owner_name);
	ft_cat(" ", buf);
	ft_cat((*attrib)->group_name, buf);
	add_spaces(buf, print->group_name_max, (*attrib)->group_name);
	free((*attrib)->group_name);
	(*buf) = majors_and_size_format((*attrib), print, itoa, buf);
	ft_cat(" ", buf);
	print->ptr = (*attrib)->timestamp;
	ft_cat((*attrib)->timestamp, buf);
	free(print->ptr);
	ft_cat(" ", buf);
	ft_cat((*attrib)->filename, buf);
	ft_cat("\n", buf);
	(*attrib) = (*attrib)->next;
}

void	print_concat_free(t_files_attrib **attrib, t_print *print, char **buf)
{
	while ((*attrib))
	{
		if ((*attrib)->error_message)
		{
			write(1, g_buf_start, (*buf) - g_buf_start);
			write(1, (*attrib)->error_message,
					ft_strlen((*attrib)->error_message));
			(*attrib) = (*attrib)->next;
			continue;
		}
		long_listing_parser(print, attrib, buf);
	}
	ft_cat("\n", buf);
	write(1, g_buf_start, (*buf) - g_buf_start);
	free(print);
	free(g_buf_start);
}
