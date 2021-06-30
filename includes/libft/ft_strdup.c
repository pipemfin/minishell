#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*s;
	int		n;
	int		i;

	i = -1;
	n = ft_strlen(str) + 1;
	if ((s = malloc(n * sizeof(char))) != NULL)
	{
		while (++i < n)
			s[i] = str[i];
		s[i] = '\0';
	}
	return (s);
}
