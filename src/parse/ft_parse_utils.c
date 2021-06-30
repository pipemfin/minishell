#include "mini.h"

char	*delete_slashe(char *str, int b)
{
	char *new;
	char *temp;

	new = NULL;
	temp = NULL;
	if (!str)
		return (NULL);
	if (b == 0)
		new = ft_strdup(&str[1]);
	else
	{
		if (str[b + 1] != '\0')
		{
			if (!(temp = ft_substr(str, b + 1, ft_strlen(&str[b]))))
				return (ft_free(str) ? NULL : NULL);
			new = ft_substr(str, 0, b);
			new = ft_realloc(new, temp);
			free(temp);
		}
		else
			new = ft_substr(str, 0, b);
	}
	free(str);
	return (new);
}

int		ft_free(char *str)
{
	free(str);
	return (0);
}

int		ft_itisword(char c, int mode)
{
	if (mode == 0 && (c == ' ' || c == '|' || c == '>' ||
		c == '<' || c == 39 || c == 34))
		return (1);
	if (mode == 1 && (c == ' ' || c == '|' || c == '>' || c == '<'))
		return (1);
	return (0);
}

char	**ft_clear_if_error(char **str, int a)
{
	while (a > -1)
	{
		free(str[a]);
		--a;
	}
	free(str);
	return (NULL);
}
