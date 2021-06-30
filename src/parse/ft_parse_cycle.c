#include "mini.h"

static int	getpi(char *str, char **buf, int *j, int *quote)
{
	int a;

	*quote = 0;
	a = 0;
	if (str && str[0] == ' ')
		while (str[a] == ' ')
			++a;
	else
	{
		*j += 1;
		a = 1;
		if (str[0] == '|')
			buf[*j] = ft_strdup("|");
		else if (str[0] == '>' && str[1] == '>' && (a = 2))
			buf[*j] = ft_strdup(">>");
		else if (str[0] == '>' && str[1] != '>')
			buf[*j] = ft_strdup(">");
		else if (str[0] == '<')
			buf[*j] = ft_strdup("<");
		if (!(buf[*j]))
			return (-1);
	}
	return (a);
}

static void	ft_parse_service_sym(char *str, int *quote, int *k, int *i)
{
	int		buf;

	buf = 0;
	*quote == 0 ? (*k = *i) : 0;
	buf = str[(*i)++];
	while (str[*i] && str[*i] != buf)
		++(*i);
	if (str[*i + 1] && !(str[*i + 1] == ' ' || str[*i + 1] == '|' ||
			str[*i + 1] == '>' || str[*i + 1] == '<'))
		*quote = 1;
	else
		*quote = 0;
	++(*i);
}

static void	ft_parse_variables(char *str, int *quote, int *k, int *i)
{
	if (*quote == 0)
		*k = *i;
	else
		*quote = 0;
	if (str[++(*i)] == '{')
	{
		while (str[*i] && str[*i] != '}' && str[*i - 1] != '\\')
			++(*i);
		++(*i);
	}
	else if (ft_isdigit(str[*i]) || str[*i] == '?')
		++(*i);
	else
		while (ft_isdigit(str[*i]) || ft_isalpha(str[*i]))
			++(*i);
	*quote = (str[*i] != '\0' && !ft_itisword(str[*i], 1)) ? 1 : 0;
}

static void	ft_parse_other_sym(char *str, int *quote, int *k, int *i)
{
	if (*quote == 0)
		*k = *i;
	else
		*quote = 0;
	while (str[++(*i)])
		if ((str[*i] == ' ' || str[*i] == '|' || str[*i] == '>' ||
			str[*i] == '<' || str[*i] == 39 || str[*i] == 34)
				&& str[*i - 1] != '\\')
			break ;
	if (str[*i] == 34 || str[*i] == 39)
		*quote = 1;
}

char		**ft_parse_cycle(char *s, t_work *w, char **m, int k)
{
	while (s[w->a] && !(w->tmp = 0))
	{
		if (ft_itisword(s[w->a], 0) && (w->a == 0 || s[w->a - 1] != '\\'))
		{
			if ((s[w->a] == 39 || s[w->a] == 34)
				&& (w->a == 0 || s[w->a - 1] != '\\'))
				ft_parse_service_sym(s, &(w->quote), &k, &(w->a));
			else if ((s[w->a] == ' ' || s[w->a] == '|' || s[w->a] == '>'
				|| s[w->a] == '<') && (w->a == 0 || s[w->a - 1] != '\\'))
			{
				if ((w->tmp = getpi(&s[w->a], m, &(w->b), &(w->quote))) == -1)
					return (ft_clear_if_error(m, w->b));
				w->a += w->tmp;
				continue ;
			}
		}
		else if (s[w->a] == 36 && (w->a == 0 || s[w->a - 1] != '\\')
			&& s[w->a + 1] && s[w->a + 1] != 32)
			ft_parse_variables(s, &(w->quote), &k, &(w->a));
		else
			ft_parse_other_sym(s, &(w->quote), &k, &(w->a));
		if (w->quote == 0 && (!(m[++(w->b)] = ft_substr(s, k, w->a - k))))
			return (ft_clear_if_error(m, w->b));
	}
	return (m);
}
