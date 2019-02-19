/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 16:44:35 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/19 21:05:53 by qhetting         ###   ########.fr       */
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

void ft_free_chain(t_files_attrib *head)
{
	t_files_attrib *nrxt;
	if ((nrxt = head->next))
	{
		while ((nrxt = nrxt->next))
		{
			free(nrxt->previous);
			free(nrxt->previous->filename);
		}
		free(head);
	}
}

void ft_free_path_chain(t_path *tail)
{
	t_path *nrxt;

	while ((nrxt = tail->next))
	{
		ft_free_chain(tail->attrib);
		free(tail);
		tail = nrxt;
	}
}

void for_each_path(t_path *pat, void (*fun)(t_files_attrib *))
{
	t_path *temp;
	if (!fun | !pat)
		return;
	temp = pat;
	while (temp)
	{
		fun(temp->attrib);
		temp = temp->next;
	}
}