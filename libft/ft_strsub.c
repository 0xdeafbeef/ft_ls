/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:50:07 by jrameau           #+#    #+#             */
/*   Updated: 2019/01/21 17:36:24 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	char	*start_ptr;

	if (!s)
		return (NULL);
	new_str = ft_strnew(len);
	if (!new_str)
		return (NULL);
	start_ptr = new_str;
	s = s + start;
	while (len--)
		*(new_str++) = *(s++);
	return (start_ptr);
}
