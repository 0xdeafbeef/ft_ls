/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 21:21:01 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/26 21:47:55 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list		*getlist(void)
{
	t_list *chain;

	chain = (t_list *)malloc(sizeof(t_list));
	return (chain);
}

t_list				*ft_lstnew(void const *content, size_t content_size)
{
	t_list *chain;

	chain = getlist();
	if (!chain)
		return (NULL);
	if (!content)
	{
		chain->next = NULL;
		chain->content = NULL;
		chain->content_size = 0;
		return (chain);
	}
	chain->content = ft_memalloc(content_size);
	if (!chain->content)
	{
		free(chain);
		return (NULL);
	}
	ft_memcpy(chain->content, (const void *)content, content_size);
	chain->content_size = content_size;
	chain->next = NULL;
	return (chain);
}
