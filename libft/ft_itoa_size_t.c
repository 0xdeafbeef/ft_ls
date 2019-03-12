/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 02:04:57 by qhetting           #+#    #+#             */
/*   Updated: 2019/02/28 16:14:49 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static size_t get_str_len(size_t n)
{
	size_t i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

char *ft_itoa_big(size_t n)
{
	char *str;
	size_t str_len;
	size_t n_cpy;

	str_len = get_str_len(n);
	n_cpy = n;

	if (!(str = ft_strnew(str_len)))
		return (NULL);
	str[--str_len] = n_cpy % 10 + '0';
	while (n_cpy /= 10)
		str[--str_len] = n_cpy % 10 + '0';
	return (str);
}
