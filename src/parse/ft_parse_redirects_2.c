#include "mini.h"

static char	*delete_quote(char *str, int b)
{
	char *new;
	char *temp;

	new = NULL;
	temp = NULL;
	if (!str)
		return (NULL);
	new = !b ? ft_strdup(&str[1]) : ft_substr(str, 0, b);
	if (b != 0 && str[b + 1] != '\0')
	{
		temp = ft_substr(str, b + 1, ft_strlen(str) - b);
		new = ft_realloc(new, temp);
		if (temp)
			free(temp);
	}
	free(str);
	return (new);
}

char		**ft_delete_element_from_array(char **array, int element_number)
{
	int		a;
	int		b;
	int		count;
	char	**new;

	a = -1;
	count = 0;
	while (array[++a] != NULL)
		++count;
	if (!(new = malloc(sizeof(char *) * (count))))
		return (NULL);
	a = -1;
	b = -1;
	while (array[++a] != NULL)
	{
		if (a == element_number)
			continue;
		if (!(new[++b] = ft_strdup(array[a])))
			return (ft_clear_if_error(new, b));
	}
	new[++b] = NULL;
	array = ft_clear_split(array);
	return (new);
}

char		*ft_del_qts(char *str, int b, int flag)
{
	int		temp_flag;

	if (!str)
		return (NULL);
	while (str[++b])
	{
		temp_flag = 0;
		if ((str[b] == 34 || str[b] == 39) && (flag == 0 || str[b] == flag))
		{
			temp_flag = str[b];
			if (!(str = delete_quote(str, b)))
				return (NULL);
			flag = flag ? 0 : temp_flag;
			--b;
		}
		else if (str[b] == '\\' && flag != 39 && ((!flag) ||
			(str[b + 1] == '$' || str[b + 1] == '"' || str[b + 1] == '\\')))
			if (!(str = delete_slashe(str, b)))
				return (NULL);
	}
	return (str);
}

char		**ft_normalize(char **str, int a, int b, int c)
{
	char	**new;
	char	**temp;

	if ((b = ft_get_new_array_size(str, -1, 0, 0)) == 0)
		return (str);
	if (!(new = malloc(sizeof(char *) * (b + 1))))
		return (NULL);
	b = -1;
	while (str[++a] != NULL && (c = -1))
		if (ft_search_space(str[a]) != 0)
		{
			valid_line(str[a], 0, 0, ' ');
			temp = ft_split(str[a], 7);
			while (temp[++c] != NULL)
				if (!(new[++b] = ft_strdup(temp[c])))
					return (ft_clear_if_error(new, b));
			ft_clear_split(temp);
		}
		else if (!(new[++b] = ft_strdup(str[a])))
			return (ft_clear_if_error(new, b));
	ft_clear_split(str);
	new[++b] = NULL;
	return (new);
}

char		**ft_del_qts_in_arr(char **array)
{
	int a;

	a = -1;
	while (array[++a] != NULL)
		if (!(array[a] = ft_del_qts(array[a], -1, 0)))
			return (ft_clear_if_error(array, a));
	return (NULL);
}
