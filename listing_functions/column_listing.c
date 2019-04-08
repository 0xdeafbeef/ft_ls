/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   column_listing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 18:27:31 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/08 23:56:46 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int				*get_longest_word(t_files_attrib *atr)
{
	int			len;
	int			cur;
	int			*prop;

	prop = ft_memalloc(sizeof(int) * 2);
	len = 0;
	while (atr)
	{
		++prop[0];
		cur = ft_strlen(atr->filename);
		if (cur > len)
			len = cur;
		atr = atr->next;
	}
	prop[1] = len;
	return (prop);
}

t_column		*column_listing_props(t_props *property, t_files_attrib *attr,
				int rec_call)
{
	int			*prop;
	int			i;
	int			j;
	t_column	*col;
	int			itter;

	if (!(property->isterm))
		return ((t_column *)normal_listing(attr, rec_call));
	i = 0;
	j = 0;
	col = ft_memalloc(sizeof(t_column));
	prop = calc_column_props(property, attr, prop, col);
	itter = !(col->vh / col->cn) ? 1 : col->vh / col->cn;
	while (i < prop[0])
	{
		if (i == itter * j)
		{
			col->attr_half[j] = attr;
			++j;
		}
		++i;
		attr = attr->next;
	}
	calc_vertical_height(prop, col);
	return (col);
}

void			print_columns_init(t_files_attrib *attr, int *i, char **buf)
{
	(*buf) = malloc(L_2_CACHE_SIZE);
	g_buf_start = (*buf);
	g_buf_end = g_buf_start + L_2_CACHE_SIZE - 1;
	(*i) = 0;
	if (g_flag & R_BIG)
		concat_full_path(attr, buf);
}

void			print_colums_on_exit(t_column *props, char **buf)
{
	ft_cat("\n", buf);
	write(1, g_buf_start, (*buf) - g_buf_start);
	free(g_buf_start);
	free(props);
}

void			print_columns(t_props *property, t_files_attrib *attr,
				int rec_call)
{
	t_column	*props;
	int			i;
	char		*buf;
	int			j;

	if (!(props = column_listing_props(property, attr, rec_call)))
		exit(0);
	print_columns_init(attr, &i, &buf);
	while (i < props->vh)
	{
		j = 0;
		while (j < props->cn)
		{
			if (props->attr_half[j])
			{
				ft_cat(props->attr_half[j]->filename, &buf);
				add_spaces(&buf, props->width, props->attr_half[j]->filename);
				props->attr_half[j] = props->attr_half[j]->next;
			}
			++j;
		}
		++i;
		ft_cat("\n", &buf);
	}
	print_colums_on_exit(props, &buf);
}
