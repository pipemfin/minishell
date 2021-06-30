#include "libft.h"

char	*ft_strchr(const char *str, int ch)
{
	int	i;
	int	n;

	i = -1;
	n = ft_strlen(str);
	while (n >= ++i)
		if (str[i] == ch)
			return ((char*)(str) + i);
	return (NULL);
}
