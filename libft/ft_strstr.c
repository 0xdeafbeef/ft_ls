/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:38:26 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/15 17:01:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *substring)
{
	int i;
	int j;
	int flag;
	int k;

	if (!ft_strlen(substring))
		return ((char *)str);
	i = -1;
	flag = 0;
	while (*(str + ++i) && !flag)
	{
		if (*(str + i) == *(substring))
		{
			j = 0;
			k = i;
			flag = 1;
			while (*(substring + j))
				if (*(substring + j++) != *(str + k++))
					flag = 0;
			if (flag)
				return ((char *)str + i);
		}
	}
	return (NULL);
}
