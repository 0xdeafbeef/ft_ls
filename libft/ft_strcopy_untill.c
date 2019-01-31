#include <libft.h>

char *ft_strcopy_until(const char *string, char ch)
{
	char *ret;
	int l;
	int i;

	i = -1;
	l = 0;
	while (string[l] != ch && l < (int)ft_strlen(string))
		l++;

	ret = ft_strnew((size_t)l);
	if (ret == NULL)
		return NULL;
	while (++i < l)
		ret[i] = string[i];
	return ret;
}