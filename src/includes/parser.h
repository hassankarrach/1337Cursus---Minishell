/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:37:40 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/23 15:56:36 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_tree
{
	int	type;
}	t_tree;

typedef struct s_logicat_operations
{
	int		type;
	t_tree	*left;
	t_tree	*right;
}	t_op;

typedef struct s_redir
{
	int				type;
	char			*hc_sep;
	char			*file_name;
	t_tree			*child;
}	t_redir;

typedef struct s_block
{
	int				type;
	t_tree			*child;
}	t_block;

typedef struct s_cmd
{
	int		type;
	int		args_number;
	char	**args;
}	t_cmd;

typedef struct s_pipe
{
	int				type;
	int				index;
	int				pipe_fd[2];
	t_tree			*left;
	t_tree			*right;
}	t_pipe;

typedef struct s_data
{
	int		flag;
	int		start;
	int		end;
	char	**args;
	t_redir	*redir;
	t_redir	*hold;
	t_redir	*hold2;
	t_cmd	*cmd;
}	t_data;

t_tree	*build_tree(t_token *head, int flag);
void	nodes_link(t_tree *node, t_tree **root);
void	logicat_operations_link(t_op *n_op, t_tree **root);
int		check_just_spaces(int flag, char **line, char *limiter);

int		count(char **args);
int		is_redir(int type);
void	init_data(t_data *data);
char	**join_arg(char **args, char *value);
t_cmd	*_cmd(char **args, int type, int i);
int		redir_node(char	***args, t_redir **hold, \
		t_token **head, t_redir **redir);
int		grass(t_token **head, t_tree **root, t_tree	*tmp, int flag);

void	linking(t_redir **hold, t_cmd *cmd, t_redir **hold2, t_tree **root);
void	logicat_operations_link(t_op *n_op, t_tree **root);
void	pipe_link(t_pipe *n_pipe, t_tree **root);
void	nodes_link(t_tree *node, t_tree **root);
void	heredoc_utils(char *tmp2, int *fd, t_redir *tmp1);

t_redir	*new_redir(t_token **head, int type);
void	new_cmd(t_token **head, t_tree **root);
void	new_block(t_tree **root, t_tree *node, t_token **head);
void	new_pipe(t_tree **root);
void	new_op(t_tree **root, int type);
int		parser(t_token *tokens);

int		print_syntax_error(void);
int		check_syntax_and_or_pipe(t_token *curr_token);
int		check_syntax_redirections(t_token *curr_token);
int		check_syntax_open_parentheses(t_token *curr_token);
int		check_syntax_close_parentheses(t_token *curr_token);

#endif
