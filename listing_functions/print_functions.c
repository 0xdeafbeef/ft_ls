#include <ft_ls.h>

#define ft_strcat strcat
#define ft_strlen strlen

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

void flush_n_erase(char **buf)
{
	*buf -= ((L2_CACHE_SIZE) - 1);
	write(1, *buf, L2_CACHE_SIZE);
	//ft_bzero(buf, L2_CACHE_SIZE); //todo maybe no bzero needed
}

void add_spaces(char *print, int *i, int count, const char *concatenated)
{
	count = (int) (1 + (count - ft_strlen(concatenated)));

	while (count--)
	{
		*print = ' ';
		++print;
		++*i;
		if (*i == L2_CACHE_SIZE)
		{
			*i = 0;
			flush_n_erase(&print);
		}
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
	int i;
	blkcnt_t size;
	char *buf;


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

	i = 0;
	while (attrib)
	{
		while (*attrib->st_mode_to_char)
		{
			*buf = *attrib->st_mode_to_char;
			++attrib->st_mode_to_char;
			++print->entry_size;
			++i;
			++buf;
			if (i == L2_CACHE_SIZE)
			{
				i = 0;
				flush_n_erase(&buf);
			}
		}
		free(attrib->st_mode_to_char - print->entry_size);
		print->entry_size = 0;
		if (i == L2_CACHE_SIZE)
		{
			i =0;
			flush_n_erase(&buf);
		}
		itoa = ft_itoa(attrib->link_count);
		add_spaces(buf, &i, print->links_max, itoa);
		while (*itoa)
		{
			*buf = *itoa;
			++itoa;
			++buf;
			++i;
			if (i == L2_CACHE_SIZE)
			{
				i = 0;
				flush_n_erase(&buf);
			}
		}
		*buf = '\n';
		++i;
		if (i == L2_CACHE_SIZE)
		{
			i =0;
			flush_n_erase(&buf);
		}
		attrib = attrib->next;
	}

	write(1, (buf -i +1), i);
}


void print_level(t_files_attrib *attrib)
{
	char *pr;

	if (!attrib)
		return;
	atribs_to_str(attrib);
}