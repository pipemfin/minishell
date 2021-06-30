#include "mini.h"

static t_list	*create_str(t_all *all, char *command)
{
	int		i;
	char	**s;
	t_list	*lst;

	lst = NULL;
	i = -1;
	if (!(ft_strncmp(command, SHELL, ft_strlen(SHELL)))
		&& ft_envp_getvalue(all->env, "COPY_1"))
		ft_lstadd_back(&lst,
			ft_lstnew(ft_strdup(ft_envp_getvalue(all->env, "COPY_1"))));
	else if (!ft_strncmp(command, "./", 2))
		ft_lstadd_back(&lst, ft_lstnew(ft_realloc(ft_realloc(ft_strdup(
				ft_envp_getvalue(all->env, "PWD")), "/"), command)));
	else if ((s = ft_split(ft_envp_getvalue(all->env, "PATH"), ':')))
	{
		while (s[++i])
			ft_lstadd_back(&lst,
				ft_lstnew(ft_realloc(ft_realloc(s[i], "/"), command)));
		free(s);
	}
	else
		return (NULL);
	return (lst);
}

static int		ft_new_process(t_all *all, char *command, char **line)
{
	pid_t	pid;

	g_flag++;
	if (!(pid = fork()))
	{
		dup2(all->commands->descript.w_fd, 1);
		dup2(all->commands->descript.r_fd, 0);
		execve(command, line, all->env_cpy);
	}
	else if (pid < 0)
		return (0);
	waitpid(pid, &g_exit, 0);
	if (g_exit == 9)
		kill(0, g_exit);
	g_flag = 0;
	g_exit == 256 ? g_exit = 1 : 0;
	return (1);
}

static char		*ft_external_check(t_all *all,
	struct stat *buf, t_list *tmp, char **line)
{
	char *str;

	str = NULL;
	if (S_ISDIR(buf->st_mode))
		ft_error(line[0], ": is a directory", 126);
	else if (!(buf->st_mode & S_IXUSR))
		ft_error(line[0], ": Permission denied", 126);
	else if (all->count_com == 1)
		ft_new_process(all, tmp->content, line);
	else
		str = ft_strdup(tmp->content);
	return (str);
}

char			*ft_external(t_all *all,
	char **line, int flag, char *str)
{
	struct stat	buf;
	t_list		*tmp[2];

	tmp[0] = NULL;
	if (!line[0][0])
		return (0);
	else if (!ft_strncmp("/", line[0], 1))
		ft_lstadd_back(&tmp[0], ft_lstnew(ft_strdup(line[0])));
	else if (!line[0] || !(tmp[0] = create_str(all, line[0])))
		flag = 3;
	tmp[1] = tmp[0];
	!ft_strncmp("/bin/cat", line[0], ft_strlen(line[0])) ||
		!ft_strncmp("cat", line[0], ft_strlen(line[0])) ? (g_flag = 2) : 0;
	while (tmp[1] && flag == 1)
		if (!stat(tmp[1]->content, &buf))
			flag = 0;
		else
			tmp[1] = tmp[1]->next;
	set_var(all->env, line);
	if (!flag)
		str = ft_external_check(all, &buf, tmp[1], line);
	else
		not_found(line[0]);
	flag != 3 ? ft_lstclear(&tmp[0], free) : 0;
	return (str);
}
