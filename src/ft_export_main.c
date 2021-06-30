#include "mini.h"
#include "command.h"

static t_envp	*ft_envp_create_without_value(char *str)
{
	t_envp	*new;

	if (!(new = malloc(sizeof(t_envp))))
		return (NULL);
	new->key_len = ft_strlen(str);
	if (!(new->key = malloc(new->key_len + 1)))
		return (NULL);
	ft_strlcpy(new->key, str, new->key_len + 1);
	new->value = NULL;
	new->value_len = 0;
	new->id = 3;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

static int		ft_export_create_without(t_envp *envp, char *str)
{
	t_envp	*copy;
	int		key_len;
	char	strcopy[ft_strlen(str) + 1];

	key_len = ft_strlen(str);
	copy = envp;
	while (copy)
	{
		if ((key_len == copy->key_len) && !ft_strncmp(copy->key, str, key_len))
		{
			copy->id = 1;
			return (0);
		}
		copy = copy->next;
	}
	ft_strlcpy(strcopy, str, key_len + 1);
	strcopy[key_len] = '\0';
	if (!ft_envp_add(&envp, ft_envp_create_without_value(strcopy)))
		return (1);
	return (0);
}

static char		**ft_export_inside(t_envp *envp, int m, char *arg, char **res)
{
	char *str;

	g_exit = 0;
	if (m == 0 && ft_export_getlist(envp, res))
		return (res);
	else if (m == 1)
	{
		if (!ft_check_identifier_export(arg))
		{
			if (ft_strchr(arg, '=') == NULL)
				ft_export_create_without(envp, arg);
			else
				ft_envp_change(envp, arg, 6, NULL);
		}
		else
		{
			g_exit = 1;
			if (!(str = ft_strjoin("export: `", &arg[0])))
				return (NULL);
			ft_error(str, "': not a valid identifier", 1);
			free(str);
		}
	}
	return (NULL);
}

char			*ft_export(t_envp *envp, char **arg)
{
	int		a;
	char	*res;

	res = NULL;
	if (arg[1] == NULL)
		return (*ft_export_inside(envp, 0, "", &res));
	else
	{
		a = 0;
		while (arg[++a] != NULL)
			ft_export_inside(envp, 1, arg[a], NULL);
		return (NULL);
	}
}
