#include "mini.h"

static int	ft_check_identifier_unset(char *str)
{
	int		a;
	int		len;

	a = -1;
	if ((len = ft_strlen(str)) == 0)
		return (1);
	while (str[++a])
		if (!ft_isalpha(str[a]))
			return (1);
	return (0);
}

int			ft_unset(t_envp *envp, char **arg)
{
	int		a;
	char	*str;

	a = 0;
	g_exit = 0;
	while (arg[++a] != NULL)
		if (!ft_check_identifier_unset(arg[a]))
			ft_delete_envp(&envp, arg[a], ft_strlen(arg[a]));
		else
		{
			if (!(str = ft_strjoin("unset: `", &arg[a][0])))
				return (ft_error("malloc", ": memory allocation error.", 1));
			ft_error(str, "': not a valid identifier", 1);
			free(str);
			return (0);
		}
	return (1);
}
