#include "mini.h"

static int	ft_echo_len(char **str)
{
	int		a;
	int		size;
	int		newline;

	newline = 1;
	a = 1;
	size = 0;
	while (ft_strlen(str[a]) == 2 && !ft_strncmp(str[a], "-n", 2))
		++a;
	while (str[a])
	{
		size += ft_strlen(str[a]) + 1;
		++a;
	}
	size--;
	return (size);
}

char		*ft_echo(t_envp *envp, char **str)
{
	int		a;
	int		b;
	int		newline;
	char	*res;

	(void)envp;
	newline = 1;
	a = 1;
	b = 0;
	g_exit = 1;
	newline = ft_strlen(str[a]) == 2 && !ft_strncmp(str[a], "-n", 2) ? 0 : 1;
	if (!(res = malloc(ft_echo_len(str) + 1 + newline)))
		return (NULL);
	while (ft_strlen(str[a]) == 2 && !ft_strncmp(str[a], "-n", 2))
		++a;
	while (str[a])
	{
		b += ft_strlcpy(&res[b], str[a], ft_strlen(str[a]) + 1);
		str[a + 1] ? b += ft_strlcpy(&res[b], " ", 2) : 0;
		++a;
	}
	newline ? res[b] = '\n' : 0;
	res[b + newline] = '\0';
	g_exit = 0;
	return (res);
}
