#include "mini.h"

static t_commands	*ft_command_create(void)
{
	t_commands	*new;

	if (!(new = malloc(sizeof(t_commands))))
		return (NULL);
	new->argument = NULL;
	new->redirects = NULL;
	new->next = NULL;
	return (new);
}

static t_commands	*ft_command_addback(t_commands **start, t_commands *new)
{
	t_commands	*last;

	if (new == NULL)
		return (NULL);
	if (!*start)
		*start = new;
	else
	{
		last = *start;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (new);
}

static char			**ft_copy_array(char **array, int size)
{
	char	**new;
	int		a;
	int		error;

	a = -1;
	error = 0;
	if (!(new = malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	while (++a < size)
	{
		if (!(new[a] = malloc(ft_strlen(array[a]) + 1)))
			return (ft_clear_if_error(new, a));
		ft_strlcpy(new[a], array[a], ft_strlen(array[a]) + 1);
	}
	new[a] = NULL;
	return (new);
}

static int			command_list_len(t_commands *list)
{
	t_commands	*temp;
	int			len;

	len = 0;
	temp = list;
	while (temp)
	{
		++len;
		temp = temp->next;
	}
	return (len);
}

t_commands			*ft_preparser(t_all *all, char *str, int i, int size)
{
	char		**buf;
	t_commands	*new;
	t_commands	*temp;

	new = NULL;
	if (!(buf = ft_parser(str)))
		return (NULL);
	while (buf[++i])
		if (!ft_strncmp(buf[i], "|", ft_strlen(buf[i])))
		{
			if ((i - size) != 0)
				if (!(temp = ft_command_addback(&new, ft_command_create()))
				|| !(temp->argument = ft_copy_array(&buf[size], i - size)))
					return (ft_clear_if_error(buf, i) ? NULL : NULL);
			size = i + 1;
		}
	if ((i - size) != 0)
		if (!(temp = ft_command_addback(&new, ft_command_create()))
		|| !(temp->argument = ft_copy_array(&buf[size], i - size)))
			return (ft_clear_if_error(buf, i) ? NULL : NULL);
	if (ft_fill_redirects(all, new, -1))
		return ((new = ft_clear_command(new)));
	all->count_com = command_list_len(new);
	ft_clear_split(buf);
	return (new);
}
