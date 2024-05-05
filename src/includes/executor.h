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
	char	*key;
	char	*value;
	int		flag;
	struct s_environment	*next;
} t_environment;

char			*ft_strdup_key(const char *s, char c);
t_environment	*new_env(char *key, char *value, int flag);

/*execution*/
void	execute();
void	start_execution(t_cmd *cmd);
int		specify_types(t_tree *node);
void	check_cmd(char **args, char	**env);
void	expand(char **str);
void	check_to_expand(char **str);
void	expansion(char ***args, int i);
int		exec_block(t_tree *node);
int		exec_and_or(t_tree *node);
int		exec_pipe(t_tree *node);
void	exec_cmd(t_tree *node);

int		args_number(char **args);
void	printf_varibles(int flag);
void	edit_environment(char *str, char *new);

/*builtins execution*/
void	builtins(char **args, int flag);
int		check_builtins(char *cmd);
void	echo_builtin(char **args);
void	cd_builtin(char **args);
void	pwd_builtin(char *str);
void	export_builtin(char **args);
void	unset_builtin(char **args);
void	env_builtin(char **args);
void	exit_builtin(char **args);
int		ft_strlen_end(char *str, char end);
void	add_back_env(t_environment *new);
void	check_validity(int *flag, char *c, char *str, int j);
void	re_create_env();
void	setup_environment(int flag);

/*exeution utils*/
void	recover_stdio();
int		ft_open_red(char *file_name, int flag);
int		in_redirection(char *file_name, int flag);
int		out_redirection(char *file_name, int flag);
void	heredoc_redirection(t_redir *redir, char *tmp, int flag, int *fd);
int		_redirections(t_redir *redir);
void	check_herdoc_to_expand(char *file_name, int *flag);
void	exec_redir(t_tree *node);
void	ft_and(l_op *and_or, int status);
void	ft_or(l_op *and_or, int status);
void	wait_loop();
void	setup_in_out_fds(int p_fd1, int p_fd2, int std_fd);
void	wait_loop();

#endif