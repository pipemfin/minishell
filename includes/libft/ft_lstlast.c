#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (lst)
	{
		while (lst)
			if (lst->next)
				lst = lst->next;
			else
				return (lst);
	}
	return (NULL);
}
