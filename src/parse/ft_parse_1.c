#include "mini.h"

static int	ft_check_service_sym(char *str, int *quote, int *k, int *flag)
{
	int i;

	i = 0;
	if ((str[i] == 39 || str[i] == 34) && (*quote == 0 || str[i] == *quote))
	{
		*flag == 0 ? ++(*k) : 0;
		*flag = 1;
		*quote = (*quote == 0) ? str[i] : 0;
		++i;
	}
	else if (str[i] == ' ')
	{
		*flag = (*quote == 0) ? 0 : 1;
		while (str[i] == ' ')
			i++;
	}
	else if ((str[i] == '|' || str[i] == '>' || str[i] == '<') && !(*quote))
	{
		++(*k);
		*flag = 0;
		i += (str[i] == '>' && str[i + 1] == '>') ? 2 : 1;
	}
	return (i);
}

static int	ft_check_variable(char *str, int *k, int *flag)
{
	int i;

	i = 0;
	*flag == 0 ? ++(*k) : 0;
	*flag = 1;
	if (str[++i] == '{')
	{
		while (str[i] && str[i] != '}' && str[i - 1] != '\\')
			++i;
		++i;
	}
	else if (ft_isdigit(str[i]) || str[i] == '?')
		++i;
	else
		while (ft_isdigit(str[i]) || ft_isalpha(str[i]))
			++i;
	return (i);
}

static int	ft_check_slashe(int *quote, int *k, int *flag)
{
	*flag == 0 ? ++(*k) : 0;
	if (*quote != 39)
		return (2);
	return (1);
}

static int	cw(char *str, int i, int k, int flag)
{
	int		quote;

	quote = 0;
	while (str[i])
		if (ft_itisword(str[i], 0) && ((quote == str[i]) || quote == 0))
			i += ft_check_service_sym(&str[i], &quote, &k, &flag);
		else if (str[i] == '\\')
			i += ft_check_slashe(&quote, &k, &flag);
		else if (str[i] == '$' && quote != 39)
			i += ft_check_variable(&str[i], &k, &flag);
		else
		{
			flag == 0 ? ++k : 0;
			flag = 1;
			while (str[++i])
				if ((str[i] == ' ' || str[i] == '|' || str[i] == '>' ||
					str[i] == '<' || str[i] == 39 || str[i] == 34) &&
						str[i - 1] != '\\')
					break ;
		}
	return (k);
}

char		**ft_parser(char *s)
{
	char	**array;
	t_work	work;

	ft_replace_init_and_exit(2, NULL, &work);
	if (!(array = malloc((cw(s, 0, 0, 0) + 1) * sizeof(char *))))
		return (NULL);
	if (!ft_parse_cycle(s, &work, array, 0))
		return (NULL);
	array[++(work.b)] = NULL;
	return (array);
}
