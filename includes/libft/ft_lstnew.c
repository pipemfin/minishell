#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list *temp;

	if ((temp = malloc(sizeof(t_list))) != NULL)
	{
		temp->content = content;
		temp->next = NULL;
	}
	return (temp);
}
