#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	int i;

	i = 0;
	if (!fd)
		return ;
	if (n == -2147483648)
		ft_putstr_fd("-2147483648", fd);
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_putnbr_fd(-n, fd);
	}
	else if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		i = n % 10 + '0';
		ft_putchar_fd((char)i, fd);
	}
	else
	{
		i = n + '0';
		ft_putchar_fd((char)i, fd);
	}
}
