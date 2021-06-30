#include "mini.h"

int			ft_envp_listlen(t_envp *envp, int envp_id)
{
	t_envp	*copy;
	int		len;

	copy = envp;
	len = 0;
	while (copy)
	{
		if (copy->id == envp_id)
			++len;
		copy = copy->next;
	}
	return (len);
}

char		**ft_clone_envp(t_envp *envp)
{
	char	**result;
	t_envp	*copy;
	int		size;
	int		a;

	copy = envp;
	size = ft_envp_listlen(envp, 1) + ft_envp_listlen(envp, 2);
	if (!(result = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	a = -1;
	while (copy)
	{
		if (copy->id == 1 || copy->id == 2)
			if (!(result[++a] = ft_substr(copy->key, 0, copy->key_len))
			|| !(result[a] = ft_realloc(result[a], "="))
			|| !(result[a] = ft_realloc(result[a], copy->value)))
				return (NULL);
		copy = copy->next;
	}
	result[size] = NULL;
	return (result);
}

char		*ft_env(t_envp *envp, char **arg)
{
	t_envp	*copy;
	char	*str;

	set_var(envp, arg);
	g_exit = 1;
	copy = envp;
	str = ft_strdup("");
	while (copy)
	{
		if (copy->id == 1)
		{
			if (!(str = ft_realloc(str, copy->key))
			|| !(str = ft_realloc(str, "="))
			|| !(str = ft_realloc(str, copy->value))
			|| !(str = ft_realloc(str, "\n")))
				return (NULL);
		}
		copy = copy->next;
	}
	g_exit = 0;
	return (str);
}

int			ft_envp_havekey(t_envp *envp, char *key)
{
	t_envp	*copy;
	int		len;

	copy = envp;
	len = ft_strlen(key);
	while (copy)
	{
		if ((len == copy->key_len) && !ft_strncmp(copy->key, &key[0], len))
			return (1);
		copy = copy->next;
	}
	return (0);
}
