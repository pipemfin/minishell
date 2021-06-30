#ifndef COMMAND_H
# define COMMAND_H
# include "libft.h"
# include <errno.h>
# include <string.h>

typedef struct		s_work
{
	int				a;
	int				b;
	int				quote;
	int				flag;
	int				tmp;
	char			*temp;
	char			*temp2;
}					t_work;

typedef struct		s_envp
{
	int				id;
	char			*key;
	int				key_len;
	char			*value;
	int				value_len;
	struct s_envp	*next;
	struct s_envp	*prev;
}					t_envp;

typedef struct		s_redir
{
	char			*command;
	char			*argument;
	struct s_redir	*next;
}					t_redir;

typedef struct		s_descript
{
	int				w_fd;
	int				r_fd;
	char			*buf;
}					t_descript;

typedef struct		s_comm
{
	char			**argument;
	t_redir			*redirects;
	t_descript		descript;
	struct s_comm	*next;
}					t_commands;

typedef struct		s_line
{
	int				result;
	char			*line1;
	char			*line2;
}					t_line;

typedef struct		s_all
{
	char			**env_cpy;
	t_line			line;
	t_envp			*env;
	char			**arg;
	t_commands		*commands;
	int				count_com;
}					t_all;

char				**ft_parser(char *s);
int					validating_string(char **str, int a);
t_commands			*ft_preparser(t_all *all, char *str, int i, int size);
int					set_var(t_envp *envp, char **command);
int					ft_error(char *str, char *err, int n);
char				*ft_echo(t_envp *envp, char **str);
char				*ft_cd(t_envp *envp, char **string);
char				*ft_pwd(t_envp *envp, char **arg);
char				*ft_export(t_envp *envp, char **arg);
int					ft_check_identifier_export(char *str);
char				*ft_export_getlist(t_envp *envp, char **str);
int					ft_unset(t_envp *envp, char **arg);
char				**ft_clone_envp(t_envp *envp);
int					ft_copy_buf(t_envp *envp_cpy, char *s, char *s2, char *s3);
int					ft_envp_copy(char **envp, t_envp **envp_cpy);
void				ft_change_id(t_envp *env, char *key, int id);
int					ft_delete_envp(t_envp **envp, char *key, int key_len);
char				*ft_envp_getvalue(t_envp *envp, char *key);
int					ft_envp_change(t_envp *envp, char *s, int mode, char *val);
char				*ft_env(t_envp *envp, char **arg);
t_envp				*ft_envp_add(t_envp **start, t_envp *new);
char				*ft_envp_getdata(char *s, char **v, int *k_l, int *v_l);
t_envp				*ft_envp_create(char *str, int id);
int					ft_envp_listlen(t_envp *envp, int envp_id);
char				*ft_external(t_all *all, char **command, int f, char *s);
int					ft_redir(t_commands *tmp, t_redir *redir);
int					ft_sing_command(t_all *all);
int					ft_multi_command(t_all *all, t_commands *tmp, int i);
t_redir				*ft_clear_redir(t_redir *redirects);
t_commands			*ft_clear_command(t_commands *command);
void				ft_free_all(t_all *all);
int					ft_envp_havekey(t_envp *envp, char *key);

char				**ft_delete_emptyelems(char **array);
t_commands			*ft_preparser(t_all *all, char *str, int i, int size);
char				**ft_clear_if_error(char **str, int a);
int					ft_itisword(char c, int mode);
int					ft_free(char *str);
char				*delete_slashe(char *str, int b);
char				*ft_replace_var(t_envp *env, char *str, int *a, int *b);
char				*ft_replace_init_and_exit(int m, char **str, t_work *work);
char				*ft_replace_var_in_str(t_envp *env, char *str);
int					ft_get_new_array_size(char **str, int a, int b, int c);
char				*ft_init_temp(char *str, char *temp, int a, int b);
int					ft_replace_processing(t_envp *env, char *str, t_work *n);
char				**ft_delete_element_from_array(char **array, int element);
char				*ft_del_qts(char *str, int b, int flag);
char				**ft_normalize(char **str, int a, int b, int c);
char				**ft_del_qts_in_arr(char **array);
int					ft_fill_redirects(t_all *all, t_commands *list, int i);
char				**ft_parser(char *s);
char				**ft_parse_cycle(char *s, t_work *w, char **m, int k);
int					ft_search_space(char *str);

#endif
