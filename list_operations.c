/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_operations.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qhetting <qhetting@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 20:46:50 by qhetting          #+#    #+#             */
/*   Updated: 2019/02/28 16:59:45 by qhetting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_ls.h"

t_files_attrib *ft_list_create(char *name, t_files_attrib *next,
							   t_files_attrib *prev)
{
	t_files_attrib *list;

	list = ft_memalloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0;
	list->next = next;
	list->previous = prev;
	return (list);
}

void ft_list_sort_all(t_props *props)
{
	t_path *path;

	path = props->path;
	while (path)
	{
		for_each_level_sort(&path->attrib, &comparator_lex);
		path = path->next;
	}
}

void for_each_level_sort(t_files_attrib **attr, t_bool
( *comp)(t_files_attrib *, t_files_attrib *))
{
	t_bool is_sorted;
	t_files_attrib *attrib;

	attrib = *attr;
	is_sorted = false;
	while (1)
	{
		if (!is_sorted)
		{
			ft_merge_sort(&attrib, comp);
			is_sorted = true;
			if (attrib->root)
				attrib->root->leaf = attrib;
			*attr = attrib;
		}
		if (attrib->leaf)
			for_each_level_sort(&attrib->leaf, comp);
		if (!attrib->next)
			break;
		attrib = attrib->next;
	}
}

t_files_attrib *ft_list_push(t_files_attrib *current, t_files_attrib *prev)
{
	current->next = NULL;
	current->previous = prev;
	prev->next = current;
	return (current);
}

t_files_attrib *create_atr(const char *name)
{
	t_files_attrib *attrib;

	attrib = ft_memalloc(sizeof(t_files_attrib));
	attrib->leaf = NULL;
	attrib->next = NULL;
	attrib->previous = NULL;
	attrib->filename = NULL;
	if (name)
		attrib->filename = ft_strdup(name);
	return (attrib);
}

void print_wrapper(t_files_attrib *attrib)
{

	print_all(attrib);
}

static unsigned short int intlen(int num)
{
	unsigned short int ret;

	ret = 0;
	while (num)
	{
		num /= 10;
		++ret;
	}
	return (ret);
}

t_print *atribs_to_str(t_files_attrib *attrib)
{
	t_print *print;
	char *itoa;
	print = ft_memalloc(sizeof(t_print));
	ft_bzero(print, sizeof(t_print));
	if (!attrib)
		return (NULL);
	while (attrib->next)
	{
		if (ft_strequ(".", attrib->filename) || ft_strequ("..", attrib->filename))
		{
			attrib = attrib->next;
			continue;
		}
		++print->verical_len;
		print->tmp = intlen(attrib->link_count);
		if (print->links_max < print->tmp)
			print->links_max = (unsigned short) print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->filename);
		if (print->owner_len_max < print->tmp)
			print->owner_len_max = print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->group_name);
		if (print->group_name_max < print->tmp)
			print->group_name_max = print->tmp;
		print->tmp = (unsigned int) ft_strlen(attrib->filename);
		if (print->max_name_len < print->tmp)
			print->max_name_len = print->tmp;
		attrib = attrib->next;
	}
	while (attrib->previous)
		attrib = attrib->previous;
	print->entry_size =
			10 + 1 + print->links_max + 1 + print->owner_len_max + 1 + print->group_name_max + 1 + print->max_name_len +
			1;
	print->result = ft_strnew(print->entry_size * print->verical_len);
	while (attrib->next)
	{
		if (ft_strequ(".", attrib->filename) || ft_strequ("..", attrib->filename))
		{
			attrib = attrib->next;
			continue;
		}
		ft_strcat(print->result, attrib->st_mode_to_char);
		ft_strcat(print->result, " ");
		//todo and leading whitespaces
		itoa = ft_itoa(attrib->link_count);
		ft_strcat(print->result, itoa);
		free(itoa);
		ft_strcat(print->result, " ");
		//todo and leading whitespaces [2]
		ft_strcat(print->result, attrib->owner_name);
		ft_strcat(print->result, " ");
		ft_strcat(print->result, attrib->group_name);
		ft_strcat(print->result, " ");
		//todo add time
		ft_strcat(print->result, attrib->filename);
		ft_strcat(print->result, "\n");
		attrib = attrib->next;
	}
	print->write_size = ft_strlen(print->result);
	return (print);
}

void print_all(t_files_attrib *attrib)
{
	t_print pr;
	t_bool isprined;

	isprined = false;
	while (attrib)
	{
		if (!isprined)
		{
			pr = *atribs_to_str(attrib);
			write(1, pr.result, pr.write_size);
			free(pr.result);
			isprined = true;
		}
		//todo finalize this
		if (attrib->leaf)
		{
			ft_putchar('\n');
			print_all(attrib->leaf);
		}
		attrib = attrib->next;
	}
}