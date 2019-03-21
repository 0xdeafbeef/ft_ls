#include <ft_ls.h>

#define ft_strcat strcat
#define ft_strlen strlen
int g_cache_state;

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

void flush_buf(char **buf)
{
	g_cache_state = 0;
	*buf = (*buf - (L2_CACHE_SIZE));
	write(1, *buf, L2_CACHE_SIZE);
}

void add_spaces(char *print, int count, const char *concatenated)
{
	count = (int) (1 + (count - ft_strlen(concatenated)));

	while (count--)
	{
		*print = ' ';
		++print;
		++g_cache_state;
		if (g_cache_state == L2_CACHE_SIZE)
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

	g_cache_state = 0;
	size = 0;
	print = ft_memalloc(sizeof(t_print));
	buf = ft_memalloc(L2_CACHE_SIZE);
	if (!attrib)
		return;
	size = get_print_props(attrib, print, size);
//	print->entry_size =
//			10 + 1 + print->links_max + 1 + print->owner_len_max + 1 +
//			print->group_name_max + 1 +
//			print->file_size_max + 1 + TIME_FORMAT_LEN + 1 +
//			print->filename_max + 1 + 5 + numlen(size) + 1;
//	print->result = ft_strnew(400+
//			print->entry_size * (print->nodes_count + 1) + print->pointers_len);
//	ft_strcat(print->result, "total ");
//	itoa = ft_itoa_big((size_t) size);
//	ft_strcat(print->result, itoa);
//	ft_strcat(print->result, "\n");
//	free(itoa);
//	while (attrib)
//	{
//		ft_strcat(print->result, attrib->st_mode_to_char);
//		itoa = ft_itoa(attrib->link_count);
//		add_spaces(print, print->links_max, itoa);
//		ft_strcat(print->result, itoa);
//		free(itoa);
//		ft_strcat(print->result, " ");
//		ft_strcat(print->result, attrib->owner_name);
//		add_spaces(print, print->owner_len_max, attrib->owner_name);
//		ft_strcat(print->result, attrib->group_name);
//		add_spaces(print, print->group_name_max, attrib->group_name);
//		itoa = ft_itoa_big(attrib->file_size);
//		add_spaces(print, print->file_size_max, itoa);
//		ft_strcat(print->result, itoa);
//		free(itoa);
//		ft_strcat(print->result, " ");
//		ft_strcat(print->result, attrib->timestamp);
//		ft_strcat(print->result, " ");
//		ft_strcat(print->result, attrib->filename);
//		if (attrib->link_pointer)
//		{
//			ft_strcat(print->result, " -> ");
//			ft_strcat(print->result, attrib->link_pointer);
//		}
//		ft_strcat(print->result, "\n");
//		attrib = attrib->next;
//	}
//	buf = print->result;
//	free(print);

	while (attrib)
	{
		print->ptr = attrib->st_mode_to_char;
		while (*attrib->st_mode_to_char) //rights
		{
			*buf = *attrib->st_mode_to_char;
			++attrib->st_mode_to_char;
			++g_cache_state;
			++buf;
			if (g_cache_state == L2_CACHE_SIZE)
				flush_buf(&buf);
		}
		//links
		free(print->ptr);
		itoa = ft_itoa(attrib->link_count);
		add_spaces(buf, print->links_max, itoa);
		while (*itoa)
		{
			*buf = *itoa;
			++itoa;
			++buf;
			++g_cache_state;
			if (g_cache_state == L2_CACHE_SIZE)
				flush_buf(&buf);
		}
		*buf = ' ';
		++buf;
		++g_cache_state;
		if (g_cache_state == L2_CACHE_SIZE)
			flush_buf(&buf);
		print->ptr = attrib->owner_name;
		while (*attrib->owner_name) //owner_name
		{
			*buf = *attrib->owner_name;
			++buf;
			++attrib->owner_name;
			++g_cache_state;
			if (g_cache_state)
				flush_buf(&buf);
		}
		add_spaces(buf, print->owner_len_max, attrib->group_name); //gr_name
		itoa = ft_itoa_big((size_t) attrib->block_size);
		add_spaces(buf, print->file_size_max, itoa);
		free(itoa);
		*buf = ' ';
		++buf;
		++g_cache_state;
		if (g_cache_state == L2_CACHE_SIZE)
			flush_buf(&buf);
		print->ptr = attrib->timestamp;
		while (*attrib->timestamp)
		{
			*buf = *attrib->timestamp;
			++buf;
			++attrib;
			++g_cache_state;
			if (g_cache_state == L2_CACHE_SIZE)
				flush_buf(&buf);
		}
		free(print->ptr);
		* buf = ' ';
		++buf;
		++g_cache_state;
		if (g_cache_state == L2_CACHE_SIZE)
			flush_buf(&buf);
		print->ptr= attrib->filename;
		while (*attrib->filename)
		{
			*buf = *attrib->filename;
			++buf;
			++attrib->filename;
			++g_cache_state;
			if (g_cache_state == L2_CACHE_SIZE)
				flush_buf(&buf);
		}
		free(print->ptr);
		* buf = '\n';
		++buf;
		++g_cache_state;
		if (g_cache_state == L2_CACHE_SIZE)
			flush_buf(&buf);
		attrib = attrib->next;
	}

	write(1, (buf - g_cache_state), g_cache_state);
}


void print_level(t_files_attrib *attrib)
{
	char *pr;

	if (!attrib)
		return;
	atribs_to_str(attrib);
}