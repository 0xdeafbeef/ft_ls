/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:36:20 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/15 17:01:19 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		ptr_mv(char **s1, const char **s2)
{
	(*s1)++;
	(*s2)++;
}

char			*ft_strncat(char *s1, const char *s2, size_t n)
{
	char		*temp;
	size_t		i;

	i = 0;
	temp = s1;
	s1 += (int)ft_strlen(s1);
	if (ft_strlen(s2) < n)
	{
		while (*s2)
		{
			*s1 = *s2;
			ptr_mv(&s1, &s2);
		}
	}
	else
	{
		while (i < n)
		{
			*s1 = *s2;
			ptr_mv(&s1, &s2);
			i++;
		}
	}
	*s1 = '\0';
	return (temp);
}
