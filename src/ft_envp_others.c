#include "command.h"

char	*ft_envp_getvalue(t_envp *envp, char *key)
{
	t_envp	*copy;
	int		key_len;

	copy = envp;
	key_len = ft_strlen(key);
	while (copy)
	{
		if ((key_len == copy->key_len)
			&& !ft_strncmp(copy->key, &key[0], key_len))
			return (copy->value);
		copy = copy->next;
	}
	return (NULL);
}

int		ft_delete_envp(t_envp **envp, char *key, int key_len)
{
	t_envp	*last;
	t_envp	*prev;

	prev = NULL;
	if (*envp == NULL)
		return (1);
	last = *envp;
	while (last)
	{
		if ((key_len == last->key_len) && !ft_strncmp(last->key, key, key_len))
		{
			if (prev)
			{
				prev->next = last->next;
				last->next ? last->next->prev = last->prev : 0;
			}
			free(last->value);
			free(last->key);
			free(last);
			return (0);
		}
		prev = last;
		last = last->next;
	}
	return (1);
}

int		ft_envp_change(t_envp *envp, char *str, int m, char *value)
{
	t_envp	*copy;
	char	*key;
	int		key_len;
	int		value_len;

	copy = envp;
	if (!(key = ft_envp_getdata(str, &value, &key_len, &value_len)))
		return (0);
	while (copy)
		if ((key_len == copy->key_len) && !ft_strncmp(copy->key, key, key_len))
		{
			free(copy->value);
			m == 6 ? copy->id = 1 : 0;
			copy->value = value;
			copy->value_len = value_len;
			free(key);
			return (0);
		}
		else
			copy = copy->next;
	m == 6 ? m = 1 : 0;
	if ((m == 1 || m == 2) && !ft_envp_add(&envp, ft_envp_create(str, m)))
		return (0);
	free(value);
	return (ft_free(key) + 1);
}

void	ft_change_id(t_envp *env, char *key, int id)
{
	t_envp	*copy;
	int		key_len;

	copy = env;
	key_len = ft_strlen(key);
	while (copy)
	{
		if ((key_len == copy->key_len) && !ft_strncmp(copy->key, key, key_len))
		{
			copy->id = id;
			break ;
		}
		copy = copy->next;
	}
}

int		ft_copy_buf(t_envp *envp_cpy, char *s1, char *s2, char *s3)
{
	char *str;

	if (!ft_envp_getvalue(envp_cpy, s1))
	{
		if (!(str = ft_strjoin(s2, ft_envp_getvalue(envp_cpy, s3))))
			return (0);
		ft_envp_change(envp_cpy, str, 2, NULL);
		free(str);
	}
	ft_change_id(envp_cpy, s1, 2);
	return (1);
}
