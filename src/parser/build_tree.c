/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:18:33 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/12 22:18:38 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return(i);
}

char	**join_arg(char **args, char *value)
{
	char	**args1;
	int		len;
	int		i;

	len = 0;
	if (args != 0)
		len = count(args);
	args1 = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while(i < len)
	{
		args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
		args1[i] = ft_strdup(args[i]);
		i++;
	}
	args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
	args1[i] = ft_strdup(value);
	args1[++i] = NULL;
	return(args1);
}

t_cmd	*_cmd(char **args ,int type, int i)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->args = args;
	new->type = type;
	new->args_number = i;
	return(new);
}

t_redir	 *new_redir(t_token **head, int type)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir));
	redir->type = type;
	redir->child = NULL;
	redir->file_name = (*head)->next->value;
	(*head) = (*head)->next->next;
	return (redir);
}
void	new_cmd(t_token **head, t_tree **root)
{
	char	**args;
	char	**tmp;
	int		i;
	t_redir *redir;
	t_redir *hold;
	t_redir *hold2;
	t_redir *tmp1;
	t_cmd	*cmd;

	args = NULL;
	redir = NULL;
	hold = NULL;
	cmd = NULL;
	i = 0;
	while ((*head) != NULL && (*head)->type != TOKEN_AND &&\
	(*head)->type != TOKEN_OR && (*head)->type != TOKEN_PIPE &&\
	 (*head)->type != TOKEN_CLOSING_PARENTHESES)
	{
		tmp = args;
		if ((*head)->type == TOKEN_APPEND_REDIRECTION || (*head)->type == TOKEN_INPUT_REDIRECTION\
		|| (*head)->type == TOKEN_OUTPUT_REDIRECTION || (*head)->type == TOKEN_HEREDOC)
		{
			tmp1 = new_redir(head, (*head)->type);
			if (redir != NULL)
			{
				redir->child = (t_tree *)tmp1;
				redir = (t_redir *)redir->child;
			}
			else
			{
				redir = tmp1;
				hold = redir;
			}
			continue ;
		}
		args = join_arg(tmp, (*head)->value);
		i++;
		ft_free(tmp);
		(*head) = (*head)->next;
	}
	if (args != NULL)
		cmd = _cmd(args, TOKEN_WORD, i);
	hold2 = hold;
	if (hold != NULL)
	{
		while (1)
		{
			if ((t_redir *)(hold->child) == NULL)
			{
				hold->child = (t_tree *)cmd;
				break ;
			}
			hold = (t_redir *)(hold->child);
		}
		nodes_link((t_tree *)hold2, root);
	}
	else
		nodes_link((t_tree *)cmd, root);
}

void	new_block(t_tree **root, t_tree *node, t_token **head)
{
	t_block *block;

	while (*head != NULL && (*head)->type != TOKEN_CLOSING_PARENTHESES)
		(*head) = (*head)->next;
	block = malloc(sizeof(t_block));
	block->child = node;
	block->type = TOKEN_BLOCK;
	nodes_link((t_tree *)block, root);
}
void	new_pipe(t_tree **root)
{
	t_pipe	*n_pipe;

	g_lobal_minishell.pipes_nbr++;
	n_pipe = malloc(sizeof(t_pipe));
	n_pipe->type = TOKEN_PIPE;
	n_pipe->left = NULL;
	n_pipe->right = NULL;
	n_pipe->index = g_lobal_minishell.pipes_nbr;
	nodes_link((t_tree *)n_pipe, root);
}

void	new_op(t_tree **root, int type)
{
	l_op	*n_op;

	n_op = malloc(sizeof(l_op));
	n_op->type = type;
	n_op->left = NULL;
	n_op->right = NULL;
	nodes_link((t_tree *)n_op, root);
}

void	logical_operations_link(l_op *n_op, t_tree **root)
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
void	nodes_link(t_tree *node, t_tree **root)
{
	if (*root == NULL)
		*root = node;
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		logical_operations_link((l_op *)node, root);
	else if (node->type == TOKEN_PIPE)
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logical_operations_link((l_op *)(*root), &node);
		pipe_link((t_pipe *)node, root);
	}
	else if (node->type == TOKEN_BLOCK)
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logical_operations_link((l_op *)(*root), &node);
		else if ((*root)->type == TOKEN_PIPE)
			pipe_link((t_pipe *)(*root), &node);
	}
	else if (node->type == TOKEN_APPEND_REDIRECTION || node->type == TOKEN_INPUT_REDIRECTION\
		|| node->type == TOKEN_OUTPUT_REDIRECTION || node->type == TOKEN_HEREDOC)
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logical_operations_link((l_op *)(*root), &node);
		else if ((*root)->type == TOKEN_PIPE)
			pipe_link((t_pipe *)(*root), &node);
	}
	else if (node->type == TOKEN_WORD)
	{
		if ((*root)->type == TOKEN_AND || (*root)->type == TOKEN_OR)
			logical_operations_link((l_op *)(*root), &node);
		else if ((*root)->type == TOKEN_PIPE)
			pipe_link((t_pipe *)(*root), &node);
	}
}


t_tree	*build_tree(t_token *head, int flag)
{
	t_tree	*root;
	t_tree	*tmp;

	root = NULL;
	tmp = NULL;
	while (head)
	{
		if (head->type == TOKEN_WORD || head->type == TOKEN_APPEND_REDIRECTION || head->type == TOKEN_INPUT_REDIRECTION\
		|| head->type == TOKEN_OUTPUT_REDIRECTION || head->type == TOKEN_HEREDOC)
		{
			new_cmd(&head, &root);
			continue ;
		}
		else if (head->type == TOKEN_PIPE)
			new_pipe(&root);
		else if (head->type == TOKEN_AND || head->type == TOKEN_OR)
			new_op(&root, head->type);
		else if (head->type == TOKEN_OPENING_PARENTHESES)
		{
			tmp = build_tree(head->next, 2);
			new_block(&root, tmp, &head);
		}
		else if (head->type == TOKEN_CLOSING_PARENTHESES)
		{
			if (flag == 2)
				return (root);
		}
		head = head->next;
	}
	return (root);
}
