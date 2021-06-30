#include "command.h"
#include <stdio.h>

char		*ft_envp_getdata(char *str, char **value, int *key_l, int *value_l)
{
	char	*key;
	char	*value_begin;

	if ((value_begin = ft_strchr(str, '=')) == NULL)
		return (NULL);
	value_begin++;
	*value_l = ft_strlen(value_begin);
	*key_l = ft_strlen(str) - *value_l - 1;
	if (!(key = ft_substr(str, 0, *key_l)))
		return (NULL);
	if (!(*value = ft_substr(value_begin, 0, *value_l)))
		if (!(*value = ft_strdup("")))
			return (key);
	return (key);
}

t_envp		*ft_envp_create(char *str, int id)
{
	t_envp	*new;

	if (!(new = malloc(sizeof(t_envp))))
		return (NULL);
	if (!(new->key = ft_envp_getdata(str, &(new->value),
		&(new->key_len), &(new->value_len))))
	{
		free(new);
		return (NULL);
	}
	new->id = id;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

t_envp		*ft_envp_add(t_envp **start, t_envp *new)
{
	t_envp	*last;

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
		new->prev = last;
	}
	return (new);
}

static int	ft_envlvl_up(char *str, t_envp *envp)
{
	int n;

	if (str && ft_isnumber(str))
	{
		ft_atoi(str, &n);
		free(str);
		if (!(str = ft_itoa(n + 1)))
			return (ft_error("malloc", ": memory allocation error.", 1));
	}
	else
	{
		if (str)
			free(str);
		if (!(str = ft_strjoin("SHLVL=", "1")))
			return (ft_error("malloc", ": memory allocation error.", 1));
		ft_envp_change(envp, str, 1, NULL);
	}
	return (1);
}

int			ft_envp_copy(char **envp, t_envp **envp_cpy)
{
	int		a;

	a = 0;
	if (!envp || !(*envp))
		return (0);
	while (envp[a] && ft_envp_add(envp_cpy, ft_envp_create(envp[a], 1)))
		a++;
	if (!ft_copy_buf(*envp_cpy, "COPY_1", "COPY_1=", "_") ||
		!ft_copy_buf(*envp_cpy, "COPY_HOME", "COPY_HOME=", "HOME"))
		return (0);
	if (!ft_envlvl_up(ft_envp_getvalue(*envp_cpy, "SHLVL"), *envp_cpy))
		return (0);
	ft_delete_envp(envp_cpy, "OLDPWD", 6);
	return (1);
}
