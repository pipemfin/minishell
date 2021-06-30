#include "libft.h"

void	*ft_memccpy(void *destination, const void *source, int c, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	unsigned char	*src;

	i = 0;
	dest = (unsigned char*)destination;
	src = (unsigned char*)source;
	if (destination == NULL && source == NULL)
		return (NULL);
	while (i < n)
	{
		dest[i] = src[i];
		if (src[i] == (unsigned char)c)
			return (destination + i + 1);
		i++;
	}
	return (NULL);
}
