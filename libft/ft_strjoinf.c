#include "libft.h"

char	*ft_strjoinf(char  *s1, char  *s2)
{
	char	*temp;

	if (!s1 || !s2)
		return (NULL);
	temp = (char *)malloc(sizeof(*temp)\
		* (ft_strlen(s1) + (ft_strlen(s2) + 1)));
	if (!temp)
		return (NULL);
	ft_strcpy(temp, s1);
	ft_strcat(temp, s2);
	free(s1);
	free(s2);
	return (temp);
}
