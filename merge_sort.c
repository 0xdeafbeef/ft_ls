/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_sort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:40 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/19 17:58:54 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

char comparator_ch(char *str1, char *str2)
{
	char ret;
	if (! str1 && str2)
		return (1);
	if (! str2 && str1)
		return (- 1);
	if (! str1 && ! str2)
		return (0);
	ret = 0;

	ret = ft_strcmp(str1, str2) > 0 ? 1 : - 1;
	return (ret);
}

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

void merge_sort(t_files_attrib **head_ref)
{
	t_files_attrib *a;
	t_files_attrib *b;
	t_files_attrib *head;

	head = *head_ref;
	if (! head || (head)->next)
		return;
	split_on_halves(head, &a, &b);
}

t_files_attrib *sorted_merge(t_files_attrib *a, t_files_attrib *b)
{
	t_files_attrib *res;

	if (! a)
		return (b);
	else
		if (! b)
			return (a);

}



