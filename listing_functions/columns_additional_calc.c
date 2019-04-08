/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   columns_additional_calc.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 23:57:12 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/08 23:57:55 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>

int		*calc_column_props(t_props *property, t_files_attrib *attr,
		int *prop, t_column *col)
{
	prop = get_longest_word(attr);
	col->vh = prop[0] + 1;
	col->width = prop[1] + 1;
	col->cn = property->win_size / col->width;
	col->cn = col->cn == 0 ? 1 : col->cn;
	col->attr_half = ft_memalloc(sizeof(attr) * (col->cn + 10));
	return (prop);
}

void	calc_vertical_height(int *prop, t_column *col)
{
	col->vh = col->vh / col->cn;
	if (!col->vh)
		col->vh = 1;
	free(prop);
}
