/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/09 20:47:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

t_files_attrib *
ft_list_create(char *name, t_files_attrib *next, t_files_attrib *prev)
{
	t_files_attrib *list;

	list = malloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0x0;
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

t_files_attrib *ft_list_add_head(t_files_attrib *current, t_files_attrib *next)
{
	if (next)
		next->previous = current;
	if (current)
	{
		current->previous = NULL;
		current->next = next;
	}
	return (current);
}

t_files_attrib *ft_list_insert(t_files_attrib *current, t_files_attrib *next,
							   t_files_attrib *prev)
{
	if (current)
	{
		current->next = next;
		current->previous = prev;
	}
	if (prev)
		prev->next = current;
	if (next)
		next->previous = current;
	return (current);

}

