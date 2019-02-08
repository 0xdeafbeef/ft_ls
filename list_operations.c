#include "ft_ls.h"

t_files_attrib *ft_list_create(char *name, t_files_attrib *next, t_files_attrib *prev)
{
	t_files_attrib *list;

	list = malloc(sizeof(t_files_attrib));
	list->filename = name ? ft_strdup(name) : 0x0;
	list->next = next;
	list->previous = prev;
	return (list);
}

t_files_attrib	*ft_list_add_tail(t_files_attrib *current, t_files_attrib *prev)
{
	prev->next = current;
	current->next = NULL;
	current->previous = prev;
	return (current);
}

t_files_attrib	*ft_list_add_head(t_files_attrib *current,t_files_attrib *next)
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

t_files_attrib	*ft_list_insert(t_files_attrib *current, t_files_attrib *next,
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

void	ft_free_chain(t_files_attrib *head)
{
	t_files_attrib *nrxt;
	if (head->next)
	{
		while((nrxt = head->next))
		{
			free(nrxt->previous->filename);
			free(nrxt->previous);
		}
		if (nrxt->filename)
			free(nrxt->filename);
		free(nrxt);
	}
}