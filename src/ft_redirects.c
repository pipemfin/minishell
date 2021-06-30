#include "mini.h"

static int	ft_redit_fd(t_descript *d, t_redir *tmp)
{
	d->w_fd != 1 && d->w_fd != -1 ? close(d->w_fd) : 0;
	d->r_fd != 0 && d->r_fd != -1 ? close(d->r_fd) : 0;
	d->w_fd = 1;
	d->r_fd = 0;
	if (!(d->buf = ft_strjoin(tmp->argument, ": ")))
		return (ft_error("malloc", ": memory allocation error.", 1));
	ft_error(d->buf, strerror(errno), 1);
	free(d->buf);
	d->buf = NULL;
	return (0);
}

static void	ft_init_desc(t_commands *tmp)
{
	tmp->descript.buf = NULL;
	tmp->descript.w_fd = 1;
	tmp->descript.r_fd = 0;
}

int			ft_redir(t_commands *tmp, t_redir *redir)
{
	ft_init_desc(tmp);
	while (redir)
	{
		if (!ft_strncmp(">\0", redir->command, 2) ||
			!ft_strncmp(">>\0", redir->command, 3))
		{
			tmp->descript.w_fd != 1 ? close(tmp->descript.w_fd) : 0;
			tmp->descript.w_fd = !ft_strncmp(">\0", redir->command, 2) ?
				open(redir->argument, O_CREAT | O_TRUNC | O_RDWR, 0644) :
					open(redir->argument, O_CREAT | O_APPEND | O_RDWR, 0644);
			if (tmp->descript.w_fd == -1)
				return (ft_redit_fd(&tmp->descript, redir));
		}
		else if (!ft_strncmp("<\0", redir->command, 2))
		{
			tmp->descript.r_fd != 0 ? close(tmp->descript.r_fd) : 0;
			if ((tmp->descript.r_fd = open(redir->argument, O_RDONLY)) == -1)
				return (ft_redit_fd(&tmp->descript, redir));
		}
		redir = redir->next;
	}
	return (1);
}
