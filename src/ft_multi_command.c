#include "mini.h"

static void	ft_close_descript(int count, int fd[count][2], int i)
{
	while (++i < count - 1)
	{
		close(fd[i][0]);
		close(fd[i][1]);
	}
}

static int	ft_wait(int i)
{
	int n;

	n = -1;
	while (++n < i)
		wait(&g_exit);
	g_exit == 256 ? g_exit = 1 : 0;
	return (1);
}

static void	ft_success_fork(t_all *all, t_commands *tmp,
	int i, int fd[all->count_com][2])
{
	if (i == 0)
	{
		tmp->next ? dup2(fd[i][1], 1) : 0;
		ft_close_descript(all->count_com, fd, -1);
	}
	else if (i < (all->count_com - 1))
	{
		dup2(fd[i - 1][0], 0);
		dup2(fd[i][1], 1);
		ft_close_descript(all->count_com, fd, -1);
	}
	else
	{
		dup2(fd[i - 1][0], 0);
		ft_close_descript(all->count_com, fd, -1);
	}
	tmp->descript.r_fd != 1 ? dup2(tmp->descript.r_fd, fd[i][0]) : 0;
	tmp->descript.w_fd != 1 ? dup2(tmp->descript.w_fd, 1) : 0;
	execve(all->line.line2, tmp->argument, all->env_cpy);
}

int			ft_multi_command(t_all *a, t_commands *t, int i)
{
	int		fd[a->count_com][2];

	while (++i < a->count_com)
		pipe(fd[i]);
	i = 0;
	while (t)
	{
		if (ft_redir(t, t->redirects))
		{
			if ((a->line.line2 = ft_external(a, t->argument, 1, NULL)))
			{
				fork() == 0 ? ft_success_fork(a, t, i, fd) : 0;
				free(a->line.line2);
				a->line.line2 = NULL;
			}
			i++;
		}
		t = t->next;
	}
	ft_close_descript(a->count_com, fd, -1);
	return (ft_wait(i));
}
