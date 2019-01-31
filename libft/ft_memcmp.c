/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:01:37 by qhetting          #+#    #+#             */
/*   Updated: 2019/01/21 17:36:24 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	const unsigned char *s1;
	const unsigned char *s2;

	s1 = (const unsigned char *)ptr1;
	s2 = (const unsigned char *)ptr2;
	while (num--)
	{
		if (*(s1) != (*(s2)))
			return (*s1 - *s2);
		else
			s1++;
		s2++;
	}
	return (0);
}
