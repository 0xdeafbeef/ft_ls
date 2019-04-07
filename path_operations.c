/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:44:35 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 16:35:18 by qhetting         ###   ########.fr       */
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

void sort_path(t_path *start)
{
	int swapped;
	t_path *ptr1;
	t_path *lptr;

	lptr = NULL;
	if (start == NULL)
		return;
	swapped = 0;
	ptr1 = start;
	while (ptr1->next != lptr)
	{
		if (comparator_lex_ch(ptr1->path, ptr1->next->path))
		{
			swap_path(ptr1, ptr1->next);
			swapped = 1;
		}
		ptr1 = ptr1->next;
	}
	lptr = ptr1;
	while (swapped)
	{
		swapped = 0;
		ptr1 = start;

		while (ptr1->next != lptr)
		{
			if (comparator_lex_ch(ptr1->path, ptr1->next->path))
			{
				swap_path(ptr1, ptr1->next);
				swapped = 1;
			}
			ptr1 = ptr1->next;
		}
		lptr = ptr1;
	}
}

/* function to swap_path data of two nodes a and b*/
void swap_path(t_path *path, t_path *path_2)
{
	char *temp;

	temp = path->path;
	path->path = path_2->path;
	path_2->path = temp;
}



