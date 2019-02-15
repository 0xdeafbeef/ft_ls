
#include <libft.h>

void *ft_realloc_gc(void **prev, size_t new_size)
{
	char *ptr;

	ptr = malloc(new_size);
	if (*prev)
	{
		ptr = ft_memcpy(ptr, *prev, new_size / 2);
		ft_bzero(*prev, new_size / 2);
		free(*prev);

	}
	return (ptr);
}