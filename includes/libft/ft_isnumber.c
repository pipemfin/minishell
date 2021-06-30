#include "libft.h"

int	ft_isnumber(char *str)
{
	int i;

	i = -1;
	if (!ft_isdigit(*str))
		return (0);
	while (str[++i])
		if (!ft_isdigit(str[i]))
			return (0);
	return (1);
}
