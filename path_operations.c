/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:44:35 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:14:49 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_path *ft_path_append_horizontal(t_path *node, char *dat)
{
	t_path *nt;

	nt = ft_memalloc(sizeof(t_path));
	if (dat)
		nt->path = ft_strdup(dat);
	nt->next = 0x0;
	if (!node)
		return (nt);
	node->next = nt;
	return (nt);
}

void sort_path(t_path **path)
{
	t_path *a;
	t_path *b;
	t_path *next;

	if(!path)
		return;
	a = *path;
	if(a->next)
		return;
	while (a)
	{
		b = a->next;
		while (b)
		{

		}
	}
}



