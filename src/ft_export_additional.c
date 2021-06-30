#include "command.h"

int			ft_check_identifier_export(char *str)
{
	int		a;
	int		len;
	int		flag;

	a = -1;
	flag = 0;
	if ((len = ft_strlen(str)) == 0)
		return (1);
	while (str[++a])
	{
		if (str[a] == '=' && a != 0)
			flag = 1;
		if (!ft_isalpha(str[a]) && flag == 0)
			return (1);
	}
	return (0);
}

static void	ft_export_swap(t_envp **first, t_envp **second)
{
	t_envp	*temp;

	temp = *first;
	*first = *second;
	*second = temp;
}

static void	ft_export_sort(t_envp **export, int len)
{
	int a;
	int b;
	int c;
	int d;

	c = len;
	b = 1;
	d = 0;
	while (c)
	{
		a = -1;
		while (++a < len - b)
		{
			if (ft_strlen(export[a]->key) > ft_strlen(export[a + 1]->key))
				d = ft_strlen(export[a]->key);
			else
				d = ft_strlen(export[a + 1]->key);
			if (ft_strncmp(export[a]->key, export[a + 1]->key, d) > 0)
				ft_export_swap(&export[a], &export[a + 1]);
		}
		++b;
		c--;
	}
}

static char	*ft_export_strmake(t_envp **ex, char **s)
{
	int		a;
	int		l;

	a = -1;
	l = 0;
	while (ex[++a] != NULL)
		l += (11 + 2 + 2 + ex[a]->key_len + ex[a]->value_len);
	if (!(*s = malloc(l + 1)))
		return (NULL);
	a = -1;
	l = 0;
	while (ex[++a] != NULL)
	{
		l += (ft_strlcpy(&(s[0][l]), "declare -x ", 12));
		l += (ft_strlcpy(&(s[0][l]), ex[a]->key, ex[a]->key_len + 1));
		if (ex[a]->value != NULL)
		{
			l += (ft_strlcpy(&(s[0][l]), "=\"", 3));
			l += (ft_strlcpy(&(s[0][l]), ex[a]->value, ex[a]->value_len + 1));
			l += (ft_strlcpy(&(s[0][l]), "\"", 2));
		}
		l += (ft_strlcpy(&(s[0][l]), "\n", 2));
	}
	(*s)[l] = '\0';
	return (*s);
}

char		*ft_export_getlist(t_envp *envp, char **str)
{
	t_envp	**export;
	t_envp	*copy;
	int		a;
	int		len;

	copy = envp;
	a = -1;
	if (!(len = ft_envp_listlen(envp, 1) + ft_envp_listlen(envp, 3)))
		return (NULL);
	if (!(export = malloc(sizeof(t_envp *) * (len + 1))))
		return (NULL);
	while (copy)
	{
		if (copy->id == 1 || copy->id == 3)
			export[++a] = copy;
		copy = copy->next;
	}
	export[++a] = NULL;
	ft_export_sort(export, len);
	if (ft_export_strmake(export, str) == NULL)
		*str = NULL;
	free(export);
	return (*str);
}
