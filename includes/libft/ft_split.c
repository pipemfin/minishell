#include "libft.h"

static int		sum_word(char const *str, char del)
{
	int	k;
	int	kol;

	k = 0;
	kol = 0;
	while (str[k] != '\0')
	{
		while (str[k] == del && str[k] != '\0')
			k++;
		if (kol++ && str[k] != del && str[k] != '\0')
			while (str[k] != del && str[k] != '\0')
				k++;
	}
	return (kol);
}

static char		*ft_word(char const *str, char del)
{
	char	*w;
	int		k;

	k = 0;
	while (str[k] && str[k] != del)
		k++;
	w = (char*)malloc(sizeof(char) * (k + 1));
	if (!w)
		return (NULL);
	k = -1;
	while (str[++k] && str[k] != del)
		w[k] = str[k];
	w[k] = '\0';
	return (w);
}

char			**ft_split(char const *s, char c)
{
	char	**str;
	int		k;
	int		i;

	k = 0;
	i = 0;
	if (!s)
		return (NULL);
	str = (char**)malloc(sizeof(char*) * (sum_word(s, c) + 1));
	if (!str)
		return (NULL);
	while (s[k])
	{
		while (s[k] == c && s[k] != '\0')
			k++;
		if (s[k] != c && s[k] != '\0')
			str[i++] = ft_word(&s[k], c);
		while (s[k] != c && s[k] != '\0')
			k++;
	}
	str[i] = NULL;
	return (str);
}
