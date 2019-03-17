#include <ft_ls.h>

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

void add_spaces(const t_print *print, int count, const char *concatenated)
{
	char *whitespaces;
	int i;

	count = (int) (1 + (count - ft_strlen(concatenated)));
	whitespaces = ft_strnew((size_t) count);
	i = 0;
	while (count--)
	{
		whitespaces[i] = ' ';
		i++;
	}
	ft_strcat(print->result, whitespaces);
	free(whitespaces);
}

t_print *atribs_to_str(t_files_attrib *attrib)
{
	t_print *print;
	char *itoa;
	t_files_attrib *holder;
	blkcnt_t size;

	size = 0;
	print = ft_memalloc(sizeof(t_print));
	if (!attrib)
		return (NULL);
	holder = attrib;
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
		attrib = attrib->next;
	}
	attrib = holder;
	print->entry_size =
			10 + 1 + print->links_max + 1 + print->owner_len_max + 1 +
			print->group_name_max + 1 +
			print->file_size_max + 1 + TIME_FORMAT_LEN + 1 +
			print->filename_max + 1 + 5 + numlen(size) + 1;
	print->result = ft_strnew(print->entry_size * (print->nodes_count + 1));
	ft_strcat(print->result, "total ");
	itoa = ft_itoa_big((size_t) size);
	ft_strcat(print->result, itoa);
	ft_strcat(print->result, "\n");
	free(itoa);
	while (attrib)
	{
		// todo .. managment
		ft_strcat(print->result, attrib->st_mode_to_char);
		itoa = ft_itoa(attrib->link_count);
		add_spaces(print, print->links_max, itoa);
		ft_strcat(print->result, itoa);
		free(itoa);
		ft_strcat(print->result, " ");
		ft_strcat(print->result, attrib->owner_name);
		add_spaces(print, print->owner_len_max, attrib->owner_name);
		ft_strcat(print->result, attrib->group_name);
		add_spaces(print, print->group_name_max, attrib->group_name);
		itoa = ft_itoa_big(attrib->file_size);
		add_spaces(print, print->file_size_max, itoa);
		ft_strcat(print->result, itoa);
		free(itoa);
		ft_strcat(print->result, " ");
		ft_strcat(print->result, attrib->timestamp);
		ft_strcat(print->result, " ");
		ft_strcat(print->result, attrib->filename);
		if (attrib->is_link)
		{
			ft_strcat(print->result, " -> ");
			ft_strcat(print->result, attrib->link_pointer);
		}
		ft_strcat(print->result, "\n");
		attrib = attrib->next;
	}
	print->write_size = ft_strlen(print->result);
	return (print);
}


void print_level(t_files_attrib *attrib)
{
	t_print *pr;

	if (!attrib)
		return;
	pr = atribs_to_str(attrib);
	write(1, pr->result, pr->write_size);
//	free(pr->result);
//	free(pr);
}

