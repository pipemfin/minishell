#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;
	int n;

	i = -1;
	if (!s || !fd)
		return ;
	n = ft_strlen(s);
	while (++i < n)
		ft_putchar_fd(s[i], fd);
}
