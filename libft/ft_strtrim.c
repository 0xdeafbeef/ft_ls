/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 19:08:26 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/16 19:18:45 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <printf.h>
#include "libft.h"

static int			wordlen(const char *s, int *i, int *j)
{
	*i = 0;
	while (s[*i] == '\n' || s[*i] == '\t' || s[*i] == ' ')
		(*i)++;
	*j = (int)ft_strlen(s) - 1;
	while (s[*j] == '\n' || s[*j] == '\t' || s[*j] == ' ')
		(*j)--;
	if ((*j - *i + 1) > 0)
		return (*j - *i + 1);
	else
		return (-1);
}

static void			mv(const char **s, char **word)
{
	(*word)++;
	(*s)++;
}

char				*ft_strtrim(char const *s)
{
	char	*word;
	char	*hand;
	int		i;
	int		j;
	size_t	k;

	if (!s)
		return (NULL);
	if (wordlen(s, &i, &j) == -1)
		return ("");
	word = ft_strnew((size_t)wordlen(s, &i, &j));
	if (word)
	{
		hand = word;
		k = (size_t)s;
		s += i;
		while ((size_t)s < (k + j) + 1)
		{
			*word = *s;
			mv(&s, &word);
		}
		return (hand);
	}
	else
		return (NULL);
}
