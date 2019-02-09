#include "ft_ls.h"

t_files_attrib *
ft_list_create(char *name, t_files_attrib *next, t_files_attrib *prev)
{
	t_files_attrib *list;

	list = malloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0x0;
	list->next = next;
	list->previous = prev;
	return (list);
}

t_files_attrib *ft_list_add_tail(t_files_attrib *current, t_files_attrib *prev)
{
	prev->next = current;
	current->next = NULL;
	current->previous = prev;
	return (current);
}

t_files_attrib *ft_list_add_head(t_files_attrib *current, t_files_attrib *next)
{
	if (next)
		next->previous = current;
	if (current)
	{
		current->previous = NULL;
		current->next = next;
	}
	return (current);
}

t_files_attrib *ft_list_insert(t_files_attrib *current, t_files_attrib *next,
							   t_files_attrib *prev)
{
	if (current)
	{
		current->next = next;
		current->previous = prev;
	}
	if (prev)
		prev->next = current;
	if (next)
		next->previous = current;
	return (current);

}

t_path *ft_path_append(t_path *node, char *dat)
{
	t_path *nt;

	nt = malloc(sizeof(t_path *));
	if (dat)
		nt->path = ft_strdup(dat);
	nt->next = 0x0;
	if (!node)
		return (nt);
	node->next = nt;
	return (nt);
}

void ft_free_chain(t_files_attrib *head)
{
	t_files_attrib *nrxt;
	if ((nrxt = head->next))
	{
		while ((nrxt = nrxt->next))
		{
			free(nrxt->previous);
			free(nrxt->previous->filename);
		}
		free(head);
	}
}

void ft_free_path_chain(t_path *tail)
{
	t_path *nrxt;


	while ((nrxt = tail->next))
	{
		ft_free_chain(tail->attrib);
		free(tail);
		tail = nrxt;
	}
}

void for_each_path(t_path *pat, void (*fun)(t_files_attrib *))
{
	t_path *temp;
	if (!fun | !pat)
		return;
	temp = pat;
	while (temp)
	{
		fun(temp->attrib);
		temp = temp->next;
	}
}
//void for_each_attrib(t_path *pat, char *data)
//{
//	t_files_attrib *next;
//	t_files_attrib *cur;
//
//	cur = pat->attrib;
//
//	while ((next = cur->next))
//
//	return;
//}