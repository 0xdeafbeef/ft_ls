/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:59:45 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

t_files_attrib *ft_list_create(char *name, t_files_attrib *next,
							   t_files_attrib *prev)
{
	t_files_attrib *list;

	list = ft_memalloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0;
	list->next = next;
	list->previous = prev;
	return (list);
}
t_files_attrib *ft_list_push(t_files_attrib *current, t_files_attrib *prev)
{
	current->next = NULL;
	current->previous = prev;
	prev->next = current;
	return (current);
}

t_files_attrib *create_atr( char *name)
{
	t_files_attrib *attrib;

	attrib = ft_memalloc(sizeof(t_files_attrib));
	if (name)
		attrib->filename = ft_strdup(name);
	return (attrib);
}
