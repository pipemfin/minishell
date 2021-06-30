#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list *temp;
	t_list *buf;

	buf = *lst;
	while (buf)
	{
		temp = buf->next;
		if (del)
			del(buf->content);
		free(buf);
		buf = temp;
	}
	*lst = NULL;
}
