#include "libft.h"

static int	ft_finder_set(char *s1, char *set, int z)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (z == -1)
		i = ft_strlen(s1) - 1;
	while (s1[i] && set[j])
	{
		if (set[j] == s1[i])
		{
			i += z;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char		*ft_strtrim(char *s1, char const *set)
{
	int		i;
	int		n;
	int		o;
	char	*buf;

	o = -1;
	if (!s1)
		return (NULL);
	if (!set)
		return (s1);
	i = ft_finder_set((char*)s1, (char*)set, 1);
	n = ft_finder_set((char*)s1, (char*)set, -1);
	if ((buf = malloc((n - i + 2) * sizeof(char))) != NULL)
	{
		while (++o <= n - i)
			buf[o] = s1[i + o];
		buf[o] = '\0';
	}
	free(s1);
	return (buf);
}
