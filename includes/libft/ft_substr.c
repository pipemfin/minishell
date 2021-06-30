#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned int	n;
	unsigned int	l;
	char			*new;

	l = (unsigned int)len;
	i = 0;
	if (!s || !(*s))
		return (NULL);
	if ((n = ft_strlen(s)) <= start)
		return (NULL);
	if (l > 0)
		n = start + l;
	else
		n = n + l;
	if ((new = malloc((n - start + 1) * sizeof(char))) != NULL)
	{
		while (len > i)
		{
			new[i] = s[i + start];
			i++;
		}
		new[i] = '\0';
	}
	return (new);
}
