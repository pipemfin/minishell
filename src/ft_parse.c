#include "mini.h"

static int	parse2(t_all *all, int i)
{
	int f;

	f = 1;
	if (validating_string(all->arg, -1))
		return (0);
	while (all->arg[++i] && f)
	{
		all->count_com = 0;
		if (!(all->commands = ft_preparser(all, all->arg[i], -1, 0)))
			return (0);
		all->env_cpy = ft_clone_envp(all->env);
		all->count_com == 1 ? (f = ft_sing_command(all))
			: ft_multi_command(all, all->commands, -1);
		all->commands = ft_clear_command(all->commands);
		all->env_cpy = ft_clear_split(all->env_cpy);
	}
	return (1);
}

int			parse(t_all *all, int a, int n)
{
	if (a == 0 && *all->line.line1)
		all->line.result = 2;
	else if (a == 0)
		all->line.result = valid_exit(NULL);
	else if (*all->line.line1)
		if (!(n = valid_line(all->line.line1, 0, 0, ';')))
			ft_error(NULL,
				"unexpected EOF while looking for matching `\"\'", 258);
		else if (n == -1)
			ft_error(NULL, "syntax error near unexpected token `;\'", 258);
		else if (n == -2)
			ft_error(NULL, "syntax error near unexpected token `;;\'", 258);
		else
		{
			if (!(all->arg = ft_split(all->line.line1, 7)))
				return (ft_error("malloc", ": memory allocation error.", 1));
			parse2(all, -1);
			all->arg = ft_clear_split(all->arg);
		}
	else
		g_exit = 0;
	return (1);
}
