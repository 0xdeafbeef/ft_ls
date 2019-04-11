/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 16:58:45 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/26 21:47:55 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	i;
	char	*p1;
	char	*p2;

	i = 0;
	p1 = (char*)dst;
	p2 = (char*)src;
	while (i < n)
	{
		*(p1 + i) = *(p2 + i);
		if (*(unsigned char*)(p2 + i) == (unsigned char)c)
			return ((char*)dst + i + 1);
		i++;
	}
	return (NULL);
}
