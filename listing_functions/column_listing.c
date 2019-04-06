#include <ft_ls.h>

int *get_longest_word(t_files_attrib *atr)
{
	int len;
	int cur;
	int *prop;

	prop = ft_memalloc(sizeof(int) * 2);
	len = 0;
	while (atr)
	{
		++*prop;
		cur = ft_strlen(atr->filename);
		if (cur > len)
			len = cur;
		atr = atr->next;
	}
	prop[1] = len;
	return (prop);
}

void column_listing(t_props *property, t_files_attrib *attr, int rec_call)
{
	unsigned short col_num;
	int *prop;
	t_files_attrib **attr_half;
	int i;
	int j;

	if (!(property->isterm))
		normal_listing(attr, rec_call);
	prop = get_longest_word(attr);
	col_num = property->win_size / (prop[0] + 1);
	attr_half = ft_memalloc(sizeof(t_files_attrib *) * col_num);
	i = 0;
	j = 0;
	while (i < prop[0])
	{
		if (prop[0] % i == 0)
		{
			attr_half[j] = attr;
			++j;
		}
		attr = attr->next;
	}
}