#include "libft.h"

char	*ft_strrchr(const char *str, int ch)
{
	int	n;

	n = ft_strlen(str) + 1;
	while (--n >= 0)
		if (str[n] == ch)
			return ((char*)(str) + n);
	return (NULL);
}
