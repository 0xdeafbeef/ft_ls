/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_misc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 00:01:32 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/09 00:04:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

unsigned char	numlen(unsigned long long int num)
{
	unsigned char ret;

	if (!num)
		return (1);
	ret = 0;
	while (num)
	{
		num /= 10;
		++ret;
	}
	return (ret);
}

void			flush_buf(char **buf_ptr)
{
	*buf_ptr = g_buf_start;
	write(1, g_buf_start, L_2_CACHE_SIZE - 1);
	fflush(stdout);
}

void			ft_cat(char *copied, char **buf)
{
	while (*copied)
	{
		if (*buf == g_buf_end)
			flush_buf(buf);
		**buf = *copied;
		++copied;
		++*buf;
	}
}

void			add_spaces(char **buf, int count, const char *concatenated)
{
	count = (int)((count - ft_strlen(concatenated)));
	while (count--)
		ft_cat(" ", buf);
}

blkcnt_t		get_print_props_inner_lookup(t_files_attrib *attrib,
				t_print *print, blkcnt_t size)
{
	size += attrib->block_size;
	++print->nodes_count;
	print->tmp = numlen((unsigned long long int)attrib->link_count);
	if (print->links_max < print->tmp)
		print->links_max = (unsigned short)print->tmp;
	print->tmp = (unsigned int)ft_strlen(attrib->owner_name);
	if (print->owner_len_max < print->tmp)
		print->owner_len_max = (unsigned int)print->tmp;
	print->tmp = (unsigned int)ft_strlen(attrib->group_name);
	if (print->group_name_max < print->tmp)
		print->group_name_max = (unsigned int)print->tmp;
	print->tmp = (unsigned int)ft_strlen(attrib->filename);
	if (print->filename_max < print->tmp)
		print->filename_max = (unsigned int)print->tmp;
	print->tmp = numlen(attrib->file_size);
	if (print->file_size_max < print->tmp)
		print->file_size_max = (unsigned int)print->tmp;
	print->tmp = numlen((unsigned long long int)attrib->minor);
	if (print->tmp > print->file_size_max)
		print->file_size_max = (unsigned int)print->tmp;
	return (size);
}
