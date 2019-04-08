#include <ft_ls.h>


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
	write(1, g_buf_start, L_2_CACHE_SIZE - 1);
	fflush(stdout);
}

void ft_cat(char *copied, char **buf)
{
	while (*copied)
	{
		if (*buf == g_buf_end)
			flush_buf(buf);
		**buf = *copied;
		++copied;
		++*buf;
	}
}

void add_spaces(char **buf, int count, const char *concatenated)
{
	count = (int) ((count - ft_strlen(concatenated)));

	while (count--)
		ft_cat(" ", buf);
}

blkcnt_t get_print_props(t_files_attrib *attrib, t_print *print, blkcnt_t size)
{
	while (attrib)
	{
		if (attrib->error_message)
		{
			attrib = attrib->next;
			continue;
		}
		++print->count;
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
		print->tmp = numlen((unsigned long long int) attrib->minor);
		if (print->tmp > print->file_size_max)
			print->file_size_max = (unsigned int) print->tmp;
		if (attrib->major || attrib->minor)
		{
			print->tmp = numlen((unsigned long long int) attrib->major);
			if (print->tmp > print->major_size)
				print->major_size = (unsigned int) print->tmp;
		}
		if (attrib->link_pointer)
			print->pointers_len += ft_strlen(attrib->link_pointer);
		attrib = attrib->next;
	}
	return size;
}


char *concat_full_path(t_files_attrib *attrib, char **buf)
{
	char *temp;

	if (!(temp = ft_strrchr(attrib->full_path, '/')))
		temp = attrib->full_path + ft_strlen(attrib->full_path);
	while (attrib->full_path != temp)
	{
		if ((*buf) == g_buf_end)
			flush_buf(buf);
		*(*buf) = *attrib->full_path;
		++(*buf);
		++attrib->full_path;
	}
	ft_cat("\n", buf);
	return (*buf);
}

void long_listing(t_files_attrib *attrib, int rec_call)
{
	t_print *print;
	char *itoa;
	blkcnt_t size;
	char *buf;

	size = 0;
	print = ft_memalloc(sizeof(t_print));
	buf = malloc(L_2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end = g_buf_start + ((L_2_CACHE_SIZE) - 1);
	size = get_print_props(attrib, print, size);
	if (rec_call)
		buf = concat_full_path(attrib, &buf);
	if (print->count > 1)
	{
		ft_cat("total ", &buf);
		itoa = ft_itoa_big((size_t) size);
		ft_cat(itoa, &buf);
		free(itoa);
		ft_cat("\n", &buf);
	}
	while (attrib)
	{
		if (attrib->error_message)
		{
			write(1, g_buf_start, buf - g_buf_start);
			write(1, attrib->error_message, ft_strlen(attrib->error_message));
			attrib = attrib->next;
			continue;
		}
		ft_cat(attrib->st_mode_to_char, &buf);//links
		ft_cat(" ", &buf);
		free(attrib->st_mode_to_char);
		itoa = ft_itoa(attrib->link_count);
		add_spaces(&buf, print->links_max, itoa);
		ft_cat(itoa, &buf);
		free(itoa);
		ft_cat(" ", &buf);
		ft_cat(attrib->owner_name, &buf);
		add_spaces(&buf, print->owner_len_max, attrib->owner_name);
		ft_cat(" ", &buf);
		ft_cat(attrib->group_name, &buf);
		add_spaces(&buf, print->group_name_max, attrib->group_name); //gr_name
		if (attrib->major)
		{
			print->has_major = 1;
			itoa = ft_itoa(attrib->major);
			add_spaces(&buf, print->major_size, itoa);
			ft_cat(" ", &buf);
			ft_cat(itoa, &buf);
			ft_cat(",", &buf);
			free(itoa);
			itoa = ft_itoa(attrib->minor);
			add_spaces(&buf, print->file_size_max, itoa);
			ft_cat(itoa, &buf);
			free(itoa);
		} else
		{
			itoa = ft_itoa_big(attrib->file_size);
			add_spaces(&buf, print->major_size, "\0");
			ft_cat("  ", &buf);
			add_spaces(&buf, print->file_size_max, itoa);
			ft_cat(itoa, &buf);
			free(itoa);
		}
		ft_cat(" ", &buf);
		print->ptr = attrib->timestamp;
		ft_cat(attrib->timestamp, &buf);
		free(print->ptr);
		ft_cat(" ", &buf);
		ft_cat(attrib->filename, &buf);
		ft_cat("\n", &buf);
		attrib = attrib->next;
	}
	ft_cat("\n", &buf);
	write(1, g_buf_start, buf - g_buf_start);
	free(print);
	free(g_buf_start);
}

int *normal_listing(t_files_attrib *attrib, int rec_call)
{
	char *buf;
	buf = malloc(L_2_CACHE_SIZE);
	g_buf_start = buf;
	g_buf_end = g_buf_start + ((L_2_CACHE_SIZE) - 1);

	if (rec_call)
		concat_full_path(attrib, &buf);
	while (attrib)
	{
		ft_cat(attrib->filename, &buf);
		ft_cat("\n", &buf);
		attrib = attrib->next;
	}
	write(1, g_buf_start, buf - g_buf_start);
	free(g_buf_start);
	return (NULL);
}

void print_level(t_files_attrib *attrib, unsigned int flag, int rec_call, t_props *props)
{
	if (!attrib)
		return;
	if (flag & L)
		long_listing(attrib, rec_call);
	else
		print_columns(props,attrib, rec_call);
}