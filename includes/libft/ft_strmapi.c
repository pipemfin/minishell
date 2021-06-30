#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	unsigned int	n;
	char			*buf;

	i = 0;
	if (!s)
		return (buf = malloc(sizeof(char)));
	n = ft_strlen(s) + 1;
	if ((buf = malloc(n * sizeof(char))) != NULL)
	{
		while (i < n)
		{
			buf[i] = f(i, s[i]);
			i++;
		}
		buf[i] = 0;
	}
	return (buf);
}
