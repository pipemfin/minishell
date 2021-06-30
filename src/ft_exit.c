#include "mini.h"

static int	valid_exit2(int i, char *command, int *res)
{
	char *tmp;

	if (i > 1 && ft_isnumber(command))
	{
		ft_error("exit: ", "too many arguments", 1);
		*res = 1;
	}
	else
	{
		if (ft_isnumber(command) ||
			(command[0] == '-' && ft_isnumber(&command[1])))
			ft_atoi(command, &g_exit);
		else
		{
			if (!(tmp = ft_strjoin("exit: ", command)))
				return (ft_error("malloc", ": memory allocation error.", 1));
			ft_error(tmp, ": numeric argument required", 255);
			free(tmp);
		}
	}
	return (1);
}

int			valid_exit(char **str)
{
	int i;
	int res;

	i = 0;
	res = 0;
	write(2, "exit\n", 5);
	if (!str)
	{
		g_exit = 0;
		return (res);
	}
	while (str[i])
		i++;
	i ? valid_exit2(i, str[0], &res) : 0;
	return (res);
}
