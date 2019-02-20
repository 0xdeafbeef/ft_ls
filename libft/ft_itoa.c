/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 02:04:57 by jrameau           #+#    #+#             */
/*   Updated: 2019/02/20 18:07:02 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <printf.h>

static int		ft_intlen(int n)
{
	int i;

	i = 0;
	if (n == 0)
		return (1);
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static int		check_and_init(int *n, char **ret)
{
	int isnegative;

	isnegative = 0;
	if ((*n) > 0)
	{
		(*ret) = ft_strnew((size_t)ft_intlen((*n)));
		isnegative = 0;
	}
	else if ((*n) < 0)
	{
		(*ret) = ft_strnew((size_t)ft_intlen((*n)) + 1);
		if (!*ret)
			*ret = NULL;
		else
		{
			*(*ret) = '-';
			(*n) *= -1;
			isnegative = 1;
		}
	}
	if (!*ret)
		*ret = NULL;
	return (isnegative);
}

static char		*getstring(int n)
{
	char *ret;

	if (n == -2147483648)
		ret = ft_strdup("-2147483648");
	else
		ret = ft_strdup("0");
	return (ret);
}

char			*ft_itoa(int n)
{
	int		isnegative;
	char	*ret;

	if (n == -2147483648 || n == 0)
	{
		ret = getstring(n);
		return (ret == NULL ? NULL : ret);
	}
	isnegative = check_and_init(&n, &ret);
	if (ret)
	{
		ret += ft_intlen(n);
		while (n)
		{
			*ret = (char)((n % 10) + '0');
			n /= 10;
			ret--;
		}
		if (isnegative)
			return (ret);
		else
			return (++ret);
	}
	else
		return (NULL);
}
