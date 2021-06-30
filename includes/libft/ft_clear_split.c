#include "libft.h"

char	**ft_clear_split(char **split)
{
	int	a;

	a = -1;
	if (split == NULL)
		return (0);
	while (split[++a] != NULL)
		free(split[a]);
	free(split);
	return (NULL);
}
