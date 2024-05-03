/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/13 10:37:40 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/13 10:37:43 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef struct s_tree
{
	int	type;
} t_tree;

typedef struct s_logical_operations
{
	int		type;
	t_tree	*left;
    t_tree	*right;
} l_op;

typedef struct s_redir
{
	int				type;
	char			*file_name;
	t_tree			*child;
} t_redir;

typedef struct s_block
{
	int				type;
	t_tree			*child;
} t_block;

typedef struct s_cmd
{
	int		type;
	int		args_number;
	char	**args;
} t_cmd;

typedef struct s_pipe
{
	int				type;
	int				index;
	int				pipe_fd[2];
	t_tree			*left;
    t_tree			*right;
} t_pipe;

t_tree	*build_tree(t_token *head, int flag);
void	nodes_link(t_tree *node, t_tree **root);
void	logical_operations_link(l_op *n_op, t_tree **root);
#endif
