#include "mini.h"

static int	validate_string2(char *c)
{
	if (!ft_strncmp("|", c, ft_strlen(c)) ||
		!ft_strncmp(">", c, ft_strlen(c)) ||
		!ft_strncmp("<", c, ft_strlen(c)) ||
		!ft_strncmp(">>", c, ft_strlen(c)))
		return (0);
	return (1);
}

static int	validate_string(char **str, int *a, int i)
{
	while (str[++i])
		if (!ft_strncmp("|", str[i], ft_strlen(str[i])))
		{
			if ((i == 0) || !str[i + 1])
			{
				*a = i;
				return (1);
			}
			else if (!validate_string2(str[i + 1]) && (*a = i + 1))
				return (1);
		}
		else if (!ft_strncmp(">", str[i], ft_strlen(str[i])) ||
			!ft_strncmp(">>", str[i], ft_strlen(str[i])) ||
			!ft_strncmp("<", str[i], ft_strlen(str[i])))
		{
			if (!str[i + 1])
			{
				*a = i;
				return (1);
			}
			else if (!validate_string2(str[i + 1]) && (*a = i + 1))
				return (1);
		}
	return (0);
}

int			validating_string(char **str, int a)
{
	int		error;
	char	**buf;
	char	*tmp;

	error = 0;
	while (str[++a])
	{
		if (!(buf = ft_parser(str[a])))
			return (!ft_error("malloc", ": memory allocation error.", 1));
		if ((error = validate_string(buf, &a, -1)))
			break ;
		buf = ft_clear_split(buf);
	}
	if (error)
	{
		if (!(tmp = ft_strjoin(buf[a], "'")))
		{
			buf = ft_clear_split(buf);
			return (!ft_error("malloc", ": memory allocation error.", 1));
		}
		ft_error("syntax error near unexpected token `", tmp, 258);
		free(tmp);
	}
	ft_clear_split(buf);
	return (error);
}
