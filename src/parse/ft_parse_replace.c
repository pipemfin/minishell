#include "mini.h"

char		*ft_replace_init_and_exit(int mode, char **str, t_work *work)
{
	if (mode == 0 || mode == 2)
	{
		work->a = 0;
		work->b = 0;
		if (mode == 2)
			work->b = -1;
		work->flag = 0;
		work->quote = 0;
		work->tmp = 0;
		work->temp = NULL;
		work->temp2 = NULL;
	}
	else if (mode == 1)
	{
		if (work->temp)
			free(*str);
		else
			return (*str);
		return (work->temp);
	}
	return (NULL);
}

char		*ft_replace_var_in_str(t_envp *env, char *str)
{
	t_work	n;

	ft_replace_init_and_exit(0, &str, &n);
	while (str[n.a] && (n.flag = 1))
	{
		if (!(ft_replace_processing(env, str, &n)))
		{
			free(str);
			return (NULL);
		}
		if (n.flag)
			++n.a;
	}
	return (ft_replace_init_and_exit(1, &str, &n));
}

int			ft_search_space(char *str)
{
	int a;
	int flag;
	int b;

	a = 0;
	flag = 0;
	b = 0;
	while (str[a])
	{
		if ((str[a] == 34 || str[a] == 39) && str[a - 1] != '\\')
			flag = str[a];
		else if (flag && ((str[a] == 34 || str[a] == 39) && str[a - 1] != '\\'))
			flag = 0;
		if (!flag && str[a] == 32)
			++b;
		++a;
	}
	return (b);
}

int			ft_get_new_array_size(char **str, int a, int b, int c)
{
	while (str[++a] != NULL)
		b += ft_search_space(str[a]);
	if (b == 0)
		return (0);
	a = -1;
	while (str[++a] != NULL)
		++c;
	return (b + c);
}

char		*ft_init_temp(char *str, char *temp, int a, int b)
{
	char *temp2;

	if (temp == NULL)
		temp = ft_substr(str, 0, a);
	else
	{
		temp2 = ft_substr(str, b, a - b);
		temp = ft_realloc(temp, temp2);
		if (temp2)
			free(temp2);
	}
	return (temp);
}
