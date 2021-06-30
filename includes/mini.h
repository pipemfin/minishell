#ifndef MINI_H
# define MINI_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <fcntl.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft.h"
# include "command.h"
# define SHELL "minishell"

int					g_exit;
int					g_flag;

int					main(int argc, char **argv, char **envp);
int					valid_line(char *line, int i, char f, char x);
int					get_next_line(char **line);
int					parse(t_all *all, int a, int n);
int					skip(char c);
int					valid_exit(char **str);
int					not_found(char *str);

#endif
