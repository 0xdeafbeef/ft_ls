#include "ft_ls.h"

t_bool comparator_lex(t_files_attrib *a, t_files_attrib *b)
{
	return (ft_strcmp(a->filename, b->filename) <= 0 ? 1 : 0);
}
