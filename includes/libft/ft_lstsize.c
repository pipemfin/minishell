#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		s;

	s = 0;
	if (lst)
		while (lst)
		{
			s++;
			lst = lst->next;
		}
	return (s);
}
