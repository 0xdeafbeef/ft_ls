#include "ft_ls.h"

t_files_list *ft_list_create(char *name, t_files_list *next, t_files_list *prev)
{
	t_files_list *list;

	list = malloc(sizeof(t_files_list));
	list->filename = name ? ft_strdup(name) : 0x0;
	list->next = next;
	list->previous = prev;
	return (list);
}

t_files_list	*ft_list_add_back(t_files_list *current, t_files_list *prev)
{
	prev->next = current;
	current->next = NULL;
	current->previous = prev;
	return (current);
}

t_files_list	*ft_list_add_head(t_files_list *current,t_files_list *next)
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

t_files_list	*ft_list_insert(t_files_list *current, t_files_list *next,
								t_files_list *prev)
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