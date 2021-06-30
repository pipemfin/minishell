#include "mini.h"

static void	ft_slashe_skip(char *str, int *quote, int *a)
{
	if (str[*a] == '\\')
	{
		if (*quote != 39)
			*a += 2;
		else
			++(*a);
	}
}

static void	ft_quote_process(char *str, int *quote, int *a)
{
	if (!(*quote) && (str[*a] == 39 || str[*a] == 34))
		*quote = str[*a];
	else if (*quote && str[*a] == *quote)
		*quote = 0;
}

static int	check_conditions(int mode, char *str, int a, int quote)
{
	if (mode == 0)
		if (str[a] == '~' && quote != 39 && (str[a + 1] == '\0' ||
			str[a + 1] == ' ' || str[a + 1] == '/') && (a == 0 ||
				str[a - 1] == '='))
			return (1);
	if (mode == 1)
		if (str[a] == '$' && str[a + 1] != '=' && quote != 39 &&
			ft_strlen(str) > 1)
			return (1);
	return (0);
}

static char	*ft_replace_tilda(t_envp *env, char *str, t_work *n, int *a)
{
	if (n->temp != NULL)
	{
		if (!(n->temp = ft_realloc(n->temp, ft_substr(str, n->b, *a - n->b))))
			return (NULL);
		if (!(n->temp = ft_realloc(n->temp,
			ft_envp_getvalue(env, "COPY_HOME"))))
			return (NULL);
	}
	else
	{
		if (!(n->temp = ft_substr(str, 0, *a)))
			return (NULL);
		if (!(n->temp = ft_realloc(n->temp,
			ft_envp_getvalue(env, "COPY_HOME"))))
			return (NULL);
	}
	n->b = *a;
	*a += 1;
	return (n->temp);
}

int			ft_replace_processing(t_envp *env, char *str, t_work *n)
{
	ft_slashe_skip(str, &(n->quote), &(n->a));
	ft_quote_process(str, &(n->quote), &(n->a));
	if (check_conditions(0, str, n->a, n->quote))
	{
		if (!(n->temp = ft_replace_tilda(env, str, n, &(n->a))))
			return (0);
	}
	else if (check_conditions(1, str, n->a, n->quote))
	{
		n->temp = ft_init_temp(str, n->temp, n->a, n->b);
		n->temp2 = ft_replace_var(env, str, &(n->a), &(n->b));
		if (!(n->temp = ft_realloc(n->temp, n->temp2)))
			return (n->temp2 ? ft_free(n->temp) : 0);
		free(n->temp2);
		n->flag = 0;
	}
	else if (str[n->a + 1] == '\0' && n->temp != NULL)
	{
		n->temp2 = ft_substr(str, n->b, n->a - n->b + 1);
		if (!(n->temp = ft_realloc(n->temp, n->temp2)))
			return (n->temp2 ? ft_free(n->temp) : 0);
		free(n->temp2);
	}
	return (1);
}
