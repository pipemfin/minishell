#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void *mem;

	if ((mem = malloc(count * size)) != NULL)
		ft_memset(mem, 0, count * size);
	return (mem);
}
