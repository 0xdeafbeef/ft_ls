/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:00:10 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/09 00:04:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

t_bool g_first_print = 1;
char *g_buf_start;
char *g_buf_end;

blkcnt_t			get_print_props(t_files_attrib *attrib, t_print *print)
{
	blkcnt_t	size;

	size = 0;
	while (attrib)
	{
		if (attrib->error_message)
		{
			attrib = attrib->next;
			continue;
		}
		++print->count;
		size = get_print_props_inner_lookup(attrib, print, size);
		if (attrib->major || attrib->minor)
		{
			print->tmp = numlen((unsigned long long int)attrib->major);
			if (print->tmp > print->major_size)
				print->major_size = (unsigned int)print->tmp;
		}
		if (attrib->link_pointer)
			print->pointers_len += ft_strlen(attrib->link_pointer);
		attrib = attrib->next;
	}
	return (size);
}

char				*concat_full_path(t_files_attrib *attrib, char **buf)
{
	char	*temp;
	char	*fp_hdnler;

	fp_hdnler = attrib->full_path;
	if (!(temp = ft_strrchr(attrib->full_path, '/')))
		temp = attrib->full_path + ft_strlen(attrib->full_path);
	if (g_first_print)
		g_first_print = 0;
	else
		ft_cat("\n", buf);
	while (attrib->full_path != temp)
	{
		if ((*buf) == g_buf_end)
			flush_buf(buf);
		*(*buf) = *attrib->full_path;
		++(*buf);
		++attrib->full_path;
	}
	ft_cat("\n", buf);
	attrib->full_path = fp_hdnler;
	return (*buf);
}

void				long_listing(t_files_attrib *attrib, int rec_call)
{
	t_print		*print;
	char		*tmp;
	blkcnt_t	size;
	char		*buf;

	print = ft_memalloc(sizeof(t_print));
	buf = malloc(L_2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end = g_buf_start + ((L_2_CACHE_SIZE) - 1);
	size = get_print_props(attrib, print);
	if (rec_call)
		buf = concat_full_path(attrib, &buf);
	if (print->count > 1)
	{
		ft_cat("total ", &buf);
		tmp = ft_itoa_big((size_t)size);
		ft_cat(tmp, &buf);
		free(tmp);
		ft_cat("\n", &buf);
	}
	print_concat_free(&attrib, print, &buf);
}

int					*normal_listing(t_files_attrib *attrib, int rec_call)
{
	char	*buf;

	buf = malloc(L_2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end = g_buf_start + ((L_2_CACHE_SIZE) - 1);
	if (rec_call)
		concat_full_path(attrib, &buf);
	while (attrib)
	{
		ft_cat(attrib->filename, &buf);
		ft_cat("\n", &buf);
		attrib = attrib->next;
	}
	write(1, g_buf_start, buf - g_buf_start);
	free(g_buf_start);
	return (NULL);
}

void				print_level(t_files_attrib *attrib, unsigned int flag,
					int rec_call, t_props *props)
{
	if (!attrib)
		return ;
	if (flag & L)
		long_listing(attrib, rec_call);
	else
		print_columns(props, attrib, rec_call);
}
