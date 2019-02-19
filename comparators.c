#include "ft_ls.h"

/* if  a->data <= b->data else */

t_bool comparator_lex_inv(t_files_attrib *a, t_files_attrib *b)
{

	char *s1;
	char *s2;

	s1 = a->filename;
	s2 = b->filename;
	while (*s1 && (*s1 == *s2))
	{
		s1 ++;
		s2 ++;
	}
	if (ft_isupper(*s1) && ft_isupper(*s2))
		return (*s1 <= *s2);
	if (! ft_isupper(*s1) && ! ft_isupper(*s2))
		return (*s1 >= *s2);
	if (! ft_isupper(*s1))
		return (1);
	else
		return (0);
}
t_bool comparator_lex(t_files_attrib *a,t_files_attrib *b)
{
	return (! (comparator_lex_inv(a, b)));
}
