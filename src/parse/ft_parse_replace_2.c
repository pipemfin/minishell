#include "mini.h"

static char	*ft_replace_other(t_envp *env, char *str, int *a, int b)
{
	char *temp2;
	char *temp3;

	temp2 = NULL;
	temp3 = NULL;
	while (str[++(*a)])
		if (!ft_isalnum(str[*a]) || str[(*a) + 1] == '\0' || str[*a] == '\"')
		{
			if (str[*a] == '\"')
				temp3 = ft_substr(str, b + 1, *a - b - 1);
			else if (str[*a + 1] == '\0' && ((*a) += 1))
				temp3 = ft_substr(str, b + 1, *a - b);
			else
				temp3 = ft_substr(str, b + 1, *a - b - 1);
			if (temp3 && ft_envp_getvalue(env, temp3))
				temp2 = ft_strdup(ft_envp_getvalue(env, temp3));
			else
				temp2 = ft_strdup("");
			if (temp3)
				free(temp3);
			break ;
		}
	return (temp2);
}

static char	*ft_replace_brace(t_envp *env, char *str, int *a, int b)
{
	char *temp2;
	char *temp3;

	temp2 = NULL;
	temp3 = NULL;
	while (str[*a] != '}')
		++(*a);
	temp3 = ft_substr(str, b + 2, *a - b - 2);
	if (temp3 && ft_envp_getvalue(env, temp3))
		temp2 = ft_strdup(ft_envp_getvalue(env, temp3));
	else
		temp2 = ft_strdup("");
	*a += 1;
	if (temp3)
		free(temp3);
	return (temp2);
}

static char	*ft_replace_digit(t_envp *env, char *str, int *a, int b)
{
	char *temp2;
	char *temp3;

	temp2 = NULL;
	temp3 = NULL;
	*a += 2;
	temp3 = ft_substr(str, b + 1, *a - 1);
	if (temp3 && ft_envp_getvalue(env, temp3))
		temp2 = ft_strdup(ft_envp_getvalue(env, temp3));
	else
		temp2 = ft_strdup("");
	if (temp3)
		free(temp3);
	return (temp2);
}

static char	*ft_replace_question(t_envp *env, char *str, int *a, int b)
{
	char *temp2;

	(void)b;
	(void)env;
	(void)str;
	temp2 = NULL;
	*a += 2;
	temp2 = ft_itoa(g_exit);
	return (temp2);
}

char		*ft_replace_var(t_envp *env, char *str, int *a, int *b)
{
	char *temp2;

	temp2 = NULL;
	*b = *a;
	if (!str[*a + 1] && (*a += 1))
		temp2 = ft_strdup("$");
	else if (str[*a + 1] == '?')
		temp2 = ft_replace_question(env, str, a, *b);
	else if (ft_isdigit(str[*a + 1]))
		temp2 = ft_replace_digit(env, str, a, *b);
	else if (str[*a + 1] == '{')
		temp2 = ft_replace_brace(env, str, a, *b);
	else
		temp2 = ft_replace_other(env, str, a, *b);
	*b = *a;
	return (temp2);
}
