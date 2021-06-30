#include "mini.h"

t_redir			*ft_clear_redir(t_redir *redirects)
{
	t_redir *tmp;
	t_redir *prev;

	tmp = redirects;
	while (tmp)
	{
		free(tmp->command);
		free(tmp->argument);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	return (NULL);
}

t_commands		*ft_clear_command(t_commands *command)
{
	t_commands *tmp;
	t_commands *prev;

	tmp = command;
	while (tmp)
	{
		tmp->argument = ft_clear_split(tmp->argument);
		tmp->redirects = ft_clear_redir(tmp->redirects);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	return (NULL);
}

static t_envp	*ft_clear_env(t_envp *env)
{
	t_envp *tmp;
	t_envp *prev;

	tmp = env;
	while (tmp)
	{
		free(tmp->key);
		free(tmp->value);
		prev = tmp;
		tmp = tmp->next;
		free(prev);
	}
	return (NULL);
}

void			ft_free_all(t_all *all)
{
	all->env_cpy = ft_clear_split(all->env_cpy);
	all->arg = ft_clear_split(all->arg);
	all->line.line1 ? free(all->line.line1) : 0;
	all->line.line2 ? free(all->line.line2) : 0;
	all->commands = ft_clear_command(all->commands);
	all->env = ft_clear_env(all->env);
}
