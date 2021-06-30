#include "mini.h"

static void	ft_init_start(t_all *all)
{
	all->env = NULL;
	all->env_cpy = NULL;
	all->line.line1 = NULL;
	all->line.line2 = NULL;
	all->count_com = 1;
	all->line.result = 1;
}

static void	listener(int sig)
{
	if (sig == 2)
	{
		g_flag == 3 ? write(1, "\n", 1) : 0;
		if (!g_flag)
		{
			write(2, "\b\b  \n", 5);
			write(2, SHELL, ft_strlen(SHELL));
			write(2, "$ ", 2);
			g_exit = 1;
		}
	}
	else if (sig == 3 && g_flag != 1)
		g_flag == 3 ? write(2, "Quit: 3\n", 9) : write(2, "\b\b  \b\b", 6);
}

static int	shell(t_all *all, int a)
{
	while (all->line.result)
	{
		if (all->line.result != 2 && write(2, SHELL, ft_strlen(SHELL)))
			write(2, "$ ", 2) && (a = get_next_line(&all->line.line1));
		else
		{
			write(2, "  \b\b", 4) && (a = get_next_line(&all->line.line2));
			all->line.line1 = ft_realloc(all->line.line1, all->line.line2);
			free(all->line.line2);
			all->line.line2 = NULL;
			if (!(all->line.line1))
				return (ft_error("malloc", ": memory allocation error.", 1));
		}
		if (!parse(all, a, 0))
			return (0);
		if (all->line.result != 2)
		{
			free(all->line.line1);
			all->line.line1 = NULL;
		}
	}
	return (1);
}

int			main(int argc, char **argv, char **envp)
{
	t_all all;

	(void)argc;
	(void)argv;
	ft_init_start(&all);
	signal(SIGINT, listener);
	signal(SIGQUIT, listener);
	if (ft_envp_copy(envp, &all.env))
		shell(&all, 0);
	ft_free_all(&all);
	return (g_exit);
}
