#include "mini.h"

static int		ft_check_redirects(char *str)
{
	if (!ft_strncmp(str, ">", ft_strlen(str)) ||
	!ft_strncmp(str, "<", ft_strlen(str)) ||
	!ft_strncmp(str, ">>", ft_strlen(str)))
		return (1);
	return (0);
}

static t_redir	*ft_redir_crt(void)
{
	t_redir	*new;

	if (!(new = malloc(sizeof(t_redir))))
		return (NULL);
	new->argument = NULL;
	new->command = NULL;
	new->next = NULL;
	return (new);
}

static t_redir	*ft_redir_addback(t_redir **start, t_redir *new)
{
	t_redir	*last;

	if (new == NULL)
		return (NULL);
	if (!*start)
		*start = new;
	else
	{
		last = *start;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

static char		**ft_rep_vars_in_arr(t_envp *env, char **str)
{
	int		a;
	char	*temp;

	a = -1;
	if (str == NULL)
		return (NULL);
	while (str[++a] != NULL)
	{
		temp = NULL;
		if ((temp = ft_replace_var_in_str(env, str[a])))
			str[a] = temp;
		else
			return (ft_clear_if_error(str, a));
	}
	return (str);
}

int				ft_fill_redirects(t_all *all, t_commands *list, int i)
{
	t_commands	*tmp;
	t_redir		*new;

	tmp = list;
	while (tmp && (i = -1))
	{
		while (tmp->argument[++i] != NULL)
			if (ft_check_redirects(tmp->argument[i]))
			{
				if (!(new = ft_redir_addback(&tmp->redirects, ft_redir_crt()))
		|| !(new->command = ft_strdup(tmp->argument[i]))
		|| !(tmp->argument = ft_delete_element_from_array(tmp->argument, i))
		|| !(new->argument = ft_del_qts(ft_strdup(tmp->argument[i]), -1, 0))
		|| !(tmp->argument = ft_delete_element_from_array(tmp->argument, i)))
					return (1);
				--i;
			}
		if (!(ft_rep_vars_in_arr(all->env, tmp->argument))
			|| !(tmp->argument = ft_normalize(tmp->argument, -1, 0, 0))
			|| (ft_del_qts_in_arr(tmp->argument))
			|| !(tmp->argument = ft_delete_emptyelems(tmp->argument)))
			return (1);
		tmp = tmp->next;
	}
	return (0);
}
