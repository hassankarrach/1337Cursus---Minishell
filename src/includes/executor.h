/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 21:26:12 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/08 21:26:15 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

typedef struct s_environment
{
	char					*key;
	char					*value;
	int						flag;
	struct s_environment	*next;
}	t_environment;

char			*ft_strdup_key(const char *s, char c);
t_environment	*new_env(char *key, char *value, int flag);

/*execution*/
void			execute(void);
void			start_execution(t_cmd *cmd);
int				specify_types(t_tree *node);
void			check_cmd(char **args, char	**env);
void			expand(char **str);
void			check_to_expand(char **str);
void			expansion(char ***args, int i);
int				exec_block(t_tree *node);
int				exec_and_or(t_tree *node);
int				exec_pipe(t_tree *node);
void			exec_cmd(t_tree *node);
void			cp_expanded(char **tmp, char **tmp1);
void			_expand(char **tmp);
void			add_the_word(t_data data, t_list **head, char *str, int end);
void			va_init(t_data *data, int *i, t_list **head, char *str);
void			check_to_expand2(int i, char *str, t_list **head, t_data *data);
void			re_create_str(char **str, t_list *head);
void			edit_args(char ***args, int nb);

int				args_number(char **args);
void			printf_varibles(int flag);
void			edit_environment(char *str, char *new);

/*builtins execution*/
void			builtins(char **args, int flag);
int				check_builtins(char *cmd);
void			echo_builtin(char **args);
void			cd_builtin(char **args);
void			pwd_builtin(char *str);
void			export_builtin(char **args);
void			unset_builtin(char **args);
void			env_builtin(char **args);
void			exit_builtin(char **args);
int				ft_strlen_end(char *str, char end);
void			add_back_env(t_environment *new);
void			check_validity(int *flag, char *c, char *str, int j);
void			re_create_env(void);
void			setup_environment(int flag);

/*check_cmd*/
void			check1(char *cmd);
char			*find_path(char *cmd, char **env);
char			*check_access(char **paths);
char			**set_cmds(char **args, char *cmd);

/*exeution utils*/
void			recover_stdio(void);
int				ft_open_red(char *file_name, int flag);
int				in_redirection(char *file_name, int flag);
int				out_redirection(char *file_name, int flag);
void			heredoc_redirection(t_redir *redir, \
				char *tmp, int flag, int *fd);
void			io_redirections(t_redir *redir);
void			re_heredoc(t_redir *redir);
void			check_herdoc_to_expand(char **file_name, int *flag);
void			exec_redir(t_tree *node);
void			ft_and(t_op *and_or, int status);
void			ft_or(t_op *and_or, int status);
void			wait_loop(void);
void			setup_in_out_fds(int p_fd1, int p_fd2, int std_fd);
size_t			ft_sublen(const char *s, char c);
void			fd_error(char *file_name);
void			setup_signals(void);
void			my_handler(int i);
void			my_handler2(int i);
void			my_handler3(int i);

#endif