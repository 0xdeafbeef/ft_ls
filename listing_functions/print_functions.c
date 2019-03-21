#include <ft_ls.h>

#define ft_strcat strcat
#define ft_strlen strlen
char *g_buf_start;
char *g_buf_end;

static unsigned char numlen(unsigned long long int num)
{
	unsigned char ret;

	if (!num)
		return (1);
	ret = 0;
	while (num)
	{
		num /= 10;
		++ret;
	}
	return (ret);
}

void flush_buf(char **buf_ptr)
{
	*buf_ptr = g_buf_start;
	write(1, g_buf_start, L2_CACHE_SIZE);
}

void add_spaces(char *print, int count, const char *concatenated)
{
	count = (int) (1 + (count - ft_strlen(concatenated)));

	while (count--)
	{
		*print = ' ';
		++print;
		if (print == g_buf_end)
			flush_buf(&print);
	}
}

blkcnt_t get_print_props(t_files_attrib *attrib, t_print *print, blkcnt_t size)
{
	while (attrib)
	{
		size += attrib->block_size;
		++print->nodes_count;
		print->tmp = numlen((unsigned long long int) attrib->link_count);
		if (print->links_max < print->tmp)
			print->links_max = (unsigned short) print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->owner_name);
		if (print->owner_len_max < print->tmp)
			print->owner_len_max = (unsigned int) print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->group_name);
		if (print->group_name_max < print->tmp)
			print->group_name_max = (unsigned int) print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->filename);
		if (print->filename_max < print->tmp)
			print->filename_max = (unsigned int) print->tmp;
		print->tmp = numlen(attrib->file_size);
		if (print->file_size_max < print->tmp)
			print->file_size_max = (unsigned int) print->tmp;
		if (attrib->link_pointer)
			print->pointers_len += ft_strlen(attrib->link_pointer);
		attrib = attrib->next;
	}
	return size;
}

void atribs_to_str(t_files_attrib *attrib)
{
	t_print *print;
	char *itoa;
	blkcnt_t size;
	char *buf;


	size = 0;
	if (!attrib)
		return;

	print = ft_memalloc(sizeof(t_print));
	buf = ft_memalloc(L2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end += (L2_CACHE_SIZE) - 1;
	size = get_print_props(attrib, print, size);
	while (attrib)
	{
		print->ptr = attrib->st_mode_to_char;
		while (*attrib->st_mode_to_char) //rights
		{
			*buf = *attrib->st_mode_to_char;
			++attrib->st_mode_to_char;
			++buf;
			if (buf == g_buf_end)
				flush_buf(&buf);
		}
		//links
		free(print->ptr);
		itoa = ft_itoa(attrib->link_count);
		add_spaces(buf, print->links_max, itoa);
		free(itoa);
		*buf = ' ';
		++buf;
		if (buf == g_buf_end)
			flush_buf(&buf);
		print->ptr = attrib->owner_name;
		while (*attrib->owner_name) //owner_name
		{
			*buf = *attrib->owner_name;
			++buf;
			++attrib->owner_name;
			if (buf == g_buf_end)
				flush_buf(&buf);
		}
		free(print->ptr);
		add_spaces(buf, print->owner_len_max, attrib->group_name); //gr_name
		free(attrib->group_name);
		itoa = ft_itoa_big((size_t) attrib->block_size);
		add_spaces(buf, print->file_size_max, itoa);
		free(itoa);
		*buf = ' ';
		++buf;
		if (buf == g_buf_end)
			flush_buf(&buf);
		print->ptr = attrib->timestamp;
		while (*attrib->timestamp)
		{
			*buf = *attrib->timestamp;
			++buf;
			++attrib;
			if (buf == g_buf_end)
				flush_buf(&buf);
		}
		free(print->ptr);
		*buf = ' ';
		++buf;
		if (buf == g_buf_end)
			flush_buf(&buf);
		print->ptr = attrib->filename;
		while (*attrib->filename)
		{
			*buf = *attrib->filename;
			++buf;
			++attrib->filename;
			if (buf == g_buf_end)
				flush_buf(&buf);
		}
		attrib->filename = print->ptr;
		*buf = '\n';
		++buf;
		if (buf == g_buf_end)
			flush_buf(&buf);
		attrib = attrib->next;
	}
	*buf = '\0';
	write(1, g_buf_start, ft_strlen(g_buf_start));
}


void print_level(t_files_attrib *attrib)
{
	char *pr;

	if (!attrib)
		return;
	atribs_to_str(attrib);
}