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
		++prop[0];
		cur = ft_strlen(atr->filename);
		if (cur > len)
			len = cur;
		atr = atr->next;
	}
	prop[1] = len;
	return (prop);
}


t_column *
column_listing_props(t_props *property, t_files_attrib *attr, int rec_call)
{
	int *prop;
	int i;
	int j;
	t_column *col;
	int itter;
	//todo remove!!!!
//	property->isterm = 1;
//	property->win_size = 356;
	if (!(property->isterm))
	{
		normal_listing(attr, rec_call);
		return NULL;
	}
	col = ft_memalloc(sizeof(t_column));
	prop = get_longest_word(attr);
	col->vertical_height_for_each = prop[0] + 1;
	col->width = prop[1] + 1;
	col->columns_num = property->win_size / col->width;
	col->attr_half = ft_memalloc(sizeof(t_files_attrib *) * col->columns_num);
	i = 0;
	j = 0;
	itter = !(col->vertical_height_for_each / col->columns_num) ? 1 :
			col->vertical_height_for_each / col->columns_num;
	while (i < prop[0])
	{
		if (i == itter * j)
		{
			col->attr_half[j] = attr;
			++j;
		}
		++i;
		attr = attr->next;
	}
	col->vertical_height_for_each =
			col->vertical_height_for_each / col->columns_num;
	if (!col->vertical_height_for_each)
		col->vertical_height_for_each = 1;
	free(prop);
	return (col);
}

void print_columns(t_props *property, t_files_attrib *attr, int rec_call)
{
	t_column *props;
	int i;
	char *buf;
	int j;

	buf = malloc(L_2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end = g_buf_start + L_2_CACHE_SIZE - 1;
	if (!(props = column_listing_props(property, attr, rec_call)))
		exit(0);
	i = 0;
	while (i < props->vertical_height_for_each)
	{
		j = 0;
		while (j < props->columns_num)
		{
			if (props->attr_half[j])
			{
				ft_cat(props->attr_half[j]->filename, &buf);
				add_spaces(&buf, props->width, props->attr_half[j]->filename);
				props->attr_half[j] = props->attr_half[j]->next;
			}
			++j;
		}
		++i;
		ft_cat("\n", &buf);
	}
	write(1, g_buf_start, buf - g_buf_start);
	free(g_buf_start);
	free(props);
}