/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:27:10 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/15 17:01:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	index;
	char	*tempo;

	src_len = ft_strlen(src);
	index = 0;
	dst_len = ft_strlen(dst);
	if (size < dst_len + 1)
		return (size + src_len);
	tempo = dst;
	while (*dst)
		dst++;
	size -= dst_len;
	while (size > 1 && *src)
	{
		*dst = *src;
		dst++;
		src++;
		size--;
	}
	*dst = '\0';
	dst = tempo;
	return (dst_len + src_len);
}
