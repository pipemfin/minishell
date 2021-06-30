#include "libft.h"

void	*ft_memmove(void *destination, const void *source, size_t n)
{
	unsigned char	*dest;
	unsigned char	*src;

	dest = (unsigned char*)destination;
	src = (unsigned char*)source;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (n < 1 || destination == source)
		return (destination);
	if (dest < src)
		while (n--)
			*dest++ = *src++;
	else
	{
		dest += n;
		src += n;
		while (n--)
			*--dest = *--src;
	}
	return (destination);
}
