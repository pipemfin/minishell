#include "mini.h"

static int	ft_write_com(t_all *all, char *(*f)(t_envp*, char**))
{
	char	*str2;

	str2 = f(all->env, all->commands->argument);
	if (str2)
	{
		write(all->commands->descript.w_fd, str2, strlen(str2));
		free(str2);
	}
	return (1);
}

static int	ft_close_fd(t_commands *str)
{
	str->descript.w_fd != 1 ? close(str->descript.w_fd) : 0;
	str->descript.r_fd != 0 ? close(str->descript.r_fd) : 0;
	return (0);
}

static int	ft_sing_command_continue(t_all *all, t_commands *str)
{
	!((!ft_strncmp(str->argument[0], "env\0", 4) ||
		!ft_strncmp(str->argument[0], SHELL, ft_strlen(SHELL))))
			? set_var(all->env, str->argument) : 0;
	ft_close_fd(str);
	return (1);
}

int			ft_sing_command(t_all *all)
{
	if (!ft_redir(all->commands, all->commands->redirects)
		|| !(all->commands->argument[0]))
		return (ft_close_fd(all->commands));
	if (!(all->commands->argument[0][0]))
		return (set_var(all->env, all->commands->argument) +
			not_found(all->commands->argument[0]));
	else if (!ft_strncmp(all->commands->argument[0], "exit\0", 5))
		return (ft_sing_command_continue(all, all->commands) &&
			(all->line.result = valid_exit(&all->commands->argument[1])));
	else if (!ft_strncmp(all->commands->argument[0], "unset\0", 6))
		ft_unset(all->env, all->commands->argument);
	else if (!ft_strncmp(all->commands->argument[0], "cd\0", 3))
		ft_write_com(all, ft_cd);
	else if (!ft_strncmp(all->commands->argument[0], "env\0", 4))
		ft_write_com(all, ft_env);
	else if (!ft_strncmp(all->commands->argument[0], "pwd\0", 4))
		ft_write_com(all, ft_pwd);
	else if (!ft_strncmp(all->commands->argument[0], "echo\0", 5))
		ft_write_com(all, ft_echo);
	else if (!ft_strncmp(all->commands->argument[0], "export\0", 7))
		ft_write_com(all, ft_export);
	else
		ft_external(all, all->commands->argument, 1, NULL);
	ft_sing_command_continue(all, all->commands);
	return ((all->line.result = 1));
}
