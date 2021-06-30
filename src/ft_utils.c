#include "mini.h"

int		valid_line(char *line, int i, char f, char x)
{
	while (ft_isspace(line[i]))
		i++;
	if (line && line[i] == ';' && line[i + 1] != ';')
		return (-1);
	while (line[i])
	{
		if (line[i] == '\\' && f != 39)
			i++;
		else if ((line[i] == 39 || line[i] == 34) && !f)
			f = line[i];
		else if (line[i] == f)
			f = 0;
		else if (!f && line[i] == x)
		{
			if (line[i] == line[i + 1])
				return (-2);
			line[i] = 7;
		}
		++i;
	}
	return (f ? 0 : 1);
}

int		not_found(char *str)
{
	if (!ft_strncmp("/", str, 1))
		ft_error(str, ": No such file or directory", 127);
	else
		ft_error(str, ": command not found", 127);
	return (0);
}

int		set_var(t_envp *envp, char **command)
{
	int		i;
	char	*str;

	i = 0;
	str = NULL;
	while (command[i + 1])
		i++;
	if (!(str = ft_strjoin("_=", command[i])))
		return (ft_error("malloc", ": memory allocation error.", 1));
	ft_envp_change(envp, str, 1, NULL);
	free(str);
	return (1);
}

char	**ft_delete_emptyelems(char **array)
{
	int i;

	i = 0;
	if (array[i] == NULL)
		return (array);
	while (array[++i] != NULL)
		if (ft_strlen(array[i]) == 0)
		{
			array = ft_delete_element_from_array(array, i);
			--i;
		}
	return (array);
}
