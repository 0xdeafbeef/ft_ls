/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:41:33 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:14:49 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t haylen;

	haylen = ft_strnlen(haystack, len);
	if (ft_strnlen(haystack, len) < ft_strlen(needle))
		return (NULL);
	i = 0;
	if (0 == (ft_strnlen(needle, len)))
		return ((char *)haystack);
	if (ft_strlen(needle) > len && ft_strlen(needle) > ft_strlen(haystack))
		return (NULL);
	while (i < haylen)
	{
		if (*haystack == *needle &&
			ft_strncmp(haystack, needle, ft_strnlen(needle, len)) == 0 &&
			((haylen - i) >=
			ft_strnlen(needle, len)))
			return (char *)(haystack);
		haystack++;
		i++;
	}
	return (NULL);
}
