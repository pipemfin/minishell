#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t dstsize;

	i = 0;
	if (!dst && !src)
		return (0);
	dstsize = ft_strlen(dst);
	if (dstsize >= size)
		return (size + ft_strlen(src));
	if (i < size)
	{
		while (i < size - dstsize - 1 && src[i])
		{
			dst[i + dstsize] = src[i];
			i++;
		}
		dst[i + dstsize] = 0;
	}
	return (ft_strlen(src) + dstsize);
}
