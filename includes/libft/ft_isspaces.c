#include "libft.h"

int	ft_isspaces(char *s)
{
	int i;

	i = -1;
	while (s[++i])
		if (!ft_isspace(s[i]))
			return (0);
	return (1);
}
