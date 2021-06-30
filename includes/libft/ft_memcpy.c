#include "libft.h"

void	*ft_memcpy(void *destination, const void *source, size_t n)
{
	size_t	i;

	i = 0;
	if (destination == NULL && source == NULL)
		return (NULL);
	while (i < n)
	{
		((char*)destination)[i] = ((char*)source)[i];
		i++;
	}
	return (destination);
}
