#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t i;
	size_t n;

	i = 0;
	if (!haystack && !needle)
		return (NULL);
	if (!(n = ft_strlen(needle)))
		return ((char*)haystack);
	if (len)
		while (haystack[i] && i < len - n + 1)
		{
			if (ft_strncmp(&haystack[i], needle, n) == 0)
				return ((char*)(haystack + i));
			i++;
		}
	return (NULL);
}
