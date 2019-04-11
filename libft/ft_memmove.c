/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:06:13 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/26 21:47:55 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				counter;

	counter = 0;
	while (counter < n)
	{
		*((char *)dst + counter) = *((char *)src + counter);
		counter++;
	}
	return (dst);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char		*dst_tempo;
	const unsigned char	*src_tempo;

	if (dst < src)
		ft_memcpy(dst, src, len);
	else if (dst > src)
	{
		dst_tempo = (unsigned char *)dst;
		src_tempo = (const unsigned char *)src;
		while (len--)
			dst_tempo[len] = src_tempo[len];
	}
	return (dst);
}
