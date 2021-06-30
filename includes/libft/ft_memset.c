#include "libft.h"

void	*ft_memset(void *destination, int c, size_t n)
{
	size_t	i;
	char	*str;

	i = 0;
	str = destination;
	while (i < n)
	{
		str[i] = c;
		i++;
	}
	return (destination);
}
