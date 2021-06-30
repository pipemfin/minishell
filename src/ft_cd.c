#include "mini.h"

static char	*ft_create_in_export(const char *s1, char *s2)
{
	char *tmp;

	if (!s1 || !s2)
		return (NULL);
	tmp = ft_strjoin(s1, s2);
	free(s2);
	return (tmp);
}

static char	*ft_no_dir(char *tmp, char *str)
{
	free(tmp);
	if (!(tmp = ft_realloc(ft_strjoin("cd: ", str), ": ")))
	{
		return (ft_error("malloc", ": memory allocation error.", 1)
		? NULL : NULL);
	}
	ft_error(tmp, strerror(errno), 1);
	free(tmp);
	free(str);
	return (NULL);
}

static char	*ft_cd_continue(t_envp *envp, char *str, int *flag)
{
	char *tmp;

	g_exit = 1;
	if (!(tmp = ft_create_in_export("OLDPWD=", getcwd(NULL, 0))))
		return (NULL);
	if (chdir(str))
		return (ft_no_dir(tmp, str));
	else
	{
		ft_envp_change(envp, tmp, 1, NULL);
		free(tmp);
	}
	if (ft_envp_havekey(envp, "PWD"))
	{
		if (!(tmp = ft_create_in_export("PWD=", getcwd(NULL, 0))))
			return (NULL);
		ft_envp_change(envp, tmp, 1, NULL);
		free(tmp);
	}
	free(str);
	g_exit = 0;
	return ((*flag) ? ft_pwd(envp, NULL) : NULL);
}

static char	*ft_check_cd(t_envp *envp, char **string)
{
	char *s;

	s = NULL;
	if (string[1])
	{
		if (string[1][0] == '\0' || ft_isspaces(string[1]))
		{
			if (!ft_envp_getvalue(envp, "HOME"))
				return (ft_error(string[0], ": HOME not set", 1)
					? NULL : NULL);
			else if (!(s = ft_strdup(ft_envp_getvalue(envp, "HOME"))))
				return (ft_error("malloc", ": memory allocation error.", 1)
					? NULL : NULL);
		}
		else if (!(s = ft_strdup(string[1])))
			return (ft_error("malloc", ": memory allocation error.", 1)
			? s : s);
	}
	else if (!string[1] && !ft_envp_getvalue(envp, "HOME"))
		return (ft_error(string[0], ": HOME not set", 1) ? NULL : NULL);
	else if (!(s = ft_strdup(ft_envp_getvalue(envp, "HOME"))))
		return (ft_error("malloc", ": memory allocation error.", 1) ? s : s);
	return (s);
}

char		*ft_cd(t_envp *envp, char **string)
{
	char	*str;
	int		flag;

	flag = 0;
	if (!(str = ft_check_cd(envp, string)))
		return (NULL);
	if (str && ft_strlen(str) == 1 && !ft_strncmp("-", str, 1) && (flag = 1))
	{
		if (ft_envp_getvalue(envp, "OLDPWD"))
		{
			free(str);
			if (!(str = ft_strdup(ft_envp_getvalue(envp, "OLDPWD"))))
				return (ft_error("malloc", ": memory allocation error.", 1)
					? str : str);
		}
		else
			return (ft_error(string[0], ": OLDPWD not set", 1) ? NULL : NULL);
	}
	return (ft_cd_continue(envp, str, &flag));
}
