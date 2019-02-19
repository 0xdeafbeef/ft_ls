/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 19:39:35 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/19 19:40:50 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
/* if  a->data <= b->data else */

void split_on_halves(t_files_attrib *source, t_files_attrib **front,
					 t_files_attrib **back)
{
	t_files_attrib *fast;
	t_files_attrib *slow;

	slow = source;
	fast = source->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			slow = slow->next;
			fast = fast->next;
		}
	}
	*front = source;
	*back = slow->next;
	slow->next = NULL;
}

void ft_merge_sort(t_files_attrib **head_ref,t_bool
( *comp)(t_files_attrib *a, t_files_attrib *b))
{
	t_files_attrib *a;
	t_files_attrib *b;
	t_files_attrib *head;

	head = *head_ref;
	if (! head || (head)->next)
		return;
	split_on_halves(head, &a, &b);
}

t_files_attrib *sorted_merge(t_files_attrib *a, t_files_attrib *b, t_bool
( *comp)(t_files_attrib *a, t_files_attrib *b))
{
	t_files_attrib *result;

	if (! a)
		return (b);
	else
		if (! b)
			return (a);
	if (comp(a, b))
	{
		result = a;
		result->next = sorted_merge(a->next, b,comp);
	} else
	{
		result = b;
		result->next = sorted_merge(a, b->next,comp);
	}
	return (result);
}



