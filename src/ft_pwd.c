#include "mini.h"

char	*ft_pwd(t_envp *envp, char **arg)
{
	char *dir;

	(void)envp;
	(void)arg;
	if (!(dir = getcwd(NULL, 0)))
		return (ft_error(NULL, strerror(errno), 1) ? NULL : NULL);
	if (!(dir = ft_realloc(dir, "\n")))
		ft_error("malloc", ": memory allocation error.", 1);
	else
		g_exit = 0;
	return (dir);
}
