#include "libft.h"

static char	*ft_create_array(unsigned int j, int min, unsigned int new)
{
	char			*buf;
	unsigned int	i;

	i = 0;
	if ((buf = ft_calloc(j + 1, 1)) != NULL)
	{
		while (j != 0)
		{
			buf[j - 1] = new % 10 + 48;
			new /= 10;
			j--;
		}
		if (min)
			buf[0] = '-';
	}
	return (buf);
}

char		*ft_itoa(int n)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	new;
	unsigned int	min;

	if (n == 0)
		return (ft_strdup("0"));
	j = 0;
	min = 0;
	if (n < 0)
	{
		min = 1;
		new = -(unsigned int)n;
		j++;
	}
	else
		new = (unsigned int)n;
	i = new;
	while (i != 0)
	{
		i /= 10;
		j++;
	}
	return (ft_create_array(j, min, new));
}
