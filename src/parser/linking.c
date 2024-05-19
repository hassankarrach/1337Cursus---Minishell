/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:06:34 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/06 15:06:36 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

void	linking(t_redir **hold, t_cmd *cmd, t_redir **hold2, t_tree **root)
{
	while (1)
	{
		if ((t_redir *)((*hold)->child) == NULL)
		{
			(*hold)->child = (t_tree *)cmd;
			break ;
		}
		(*hold) = (t_redir *)((*hold)->child);
	}
	nodes_link((t_tree *)(*hold2), root);
}

void	logicat_operations_link(t_op *n_op, t_tree **root)
{
	if (n_op->left == NULL)
		n_op->left = *root;
	else
		n_op->right = *root;
	*root = (t_tree *)n_op;
}

void	pipe_link(t_pipe *n_pipe, t_tree **root)
{
	if (n_pipe->left == NULL)
		n_pipe->left = *root;
	else
		n_pipe->right = *root;
	*root = (t_tree *)n_pipe;
}

/* check for whitespace token */
void	nodes_link(t_tree *node, t_tree **root)
{
	if (*root == NULL)
		*root = node;
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		logicat_operations_link((t_op *)node, root);
	else if (node->type == TOKEN_PIPE)
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logicat_operations_link((t_op *)(*root), &node);
		pipe_link((t_pipe *)node, root);
	}
	else
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logicat_operations_link((t_op *)(*root), &node);
		else if ((*root)->type == TOKEN_PIPE)
			pipe_link((t_pipe *)(*root), &node);
	}
}
