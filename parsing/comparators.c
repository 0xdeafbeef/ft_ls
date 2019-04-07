/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comparators.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 16:06:57 by qhetting          #+#    #+#             */
/*   Updated: 2019/04/07 16:11:48 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool		comparator_lex_inv(t_files_attrib *a, t_files_attrib *b)
{
	char	*s1;
	char	*s2;

	s1 = a->filename;
	s2 = b->filename;
	while (*s1 && *s2 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	if (*s1 < *s2)
		return (0);
	if (*s2 < *s1)
		return (1);
	return (0);
}

t_bool		comparator_lex(t_files_attrib *a, t_files_attrib *b)
{
	return (!(comparator_lex_inv(a, b)));
}

t_bool		comparator_lex_inv_ch(char *a, char *b)
{
	char	*s1;
	char	*s2;

	s1 = a;
	s2 = b;
	while (*s1 && *s2 && (*s1 == *s2))
	{
		++s1;
		++s2;
	}
	if (*s1 < *s2)
		return (0);
	if (*s2 < *s1)
		return (1);
	return (0);
}

t_bool		comparator_lex_ch(char *a, char *b)
{
	return (!(comparator_lex_inv_ch(a, b)));
}

t_bool		comparator_time(t_files_attrib *a, t_files_attrib *b)
{
	if (a->time == b->time)
		return (comparator_lex_ch(a->filename, b->filename));
	if (a->time > b->time)
		return (true);
	else
		return (false);
}
