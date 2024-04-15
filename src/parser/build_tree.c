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

/*================================================================*/
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

t_cmd	*_cmd(char **args ,int type)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->args = args;
	new->type = type;
	return(new);
}
// new_nodes
void	new_cmd(t_token **head, t_tree **root)
{
	char	**args;
	char	**tmp;
	t_cmd	*cmd;

	args = NULL;
	while ((*head) != NULL && (*head)->type == TOKEN_WORD)
	{
		tmp = args;
		args = join_arg(tmp, (*head)->value);
		ft_free(tmp);
		(*head) = (*head)->next;
	}
	cmd = _cmd(args, TOKEN_WORD);
	nodes_link((t_tree *)cmd, root);
}
void	new_block(t_tree **root, t_tree *node)
{
	t_block *block;

	block = malloc(sizeof(t_block *));
	block->child = node;
	nodes_link((t_tree *)block, root);
}
void	new_redir(t_token **head, t_tree **root, t_tree *node)
{
	t_redir *redir;

	redir = malloc(sizeof(t_redir *));
	redir->child = node;
	if ((*head)->next->type == TOKEN_WORD)
		redir->file_name = (*head)->next->value;
	(*head) = (*head)->next;
	nodes_link((t_tree *)redir, root);
}
/*================================================================*/
// linking utils
void	logical_operations_link(l_op *n_op, t_tree **root)
{
	if (n_op->left == NULL)
		n_op->left = *root;
	else
		n_op->right = *root;
}
void	pipe_link(t_pipe *n_pipe, t_tree **root)
{
	if (n_pipe->left == NULL)
		n_pipe->left = *root;
	else
		n_pipe->right = *root;
}
//1 principal function for link 
void	nodes_link(t_tree *node, t_tree **root)
{
	t_pipe	*n_pipe;
	l_op	*n_op;

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


//2 loop for the list come from tokenizer

/* TODO : update tokenizer to change the order of 
node cmd and nodes redir "redir alwas first" */

t_tree	*build_tree(t_token *head, int flag)
{
	t_tree	*root;
	t_tree	*tmp;

	root = NULL;
	tmp = NULL;
	if(!head)
		root = NULL;
	while (head)
	{
		if (head->type == TOKEN_WORD)
		{
			new_cmd(&head, &root);
			if (flag == 1)
				return (root);
			continue;
		}
		else if (head->type == TOKEN_APPEND_REDIRECTION || head->type == TOKEN_INPUT_REDIRECTION\
		|| head->type == TOKEN_OUTPUT_REDIRECTION || head->type == TOKEN_HEREDOC)
		{
			tmp = build_tree(head->next->next, 1);
			new_redir(&head, &root, tmp);
			continue;
		}
		else if (head->type == TOKEN_OPENING_PARENTHESES)
		{
			tmp = build_tree(head->next, 0);
			new_block(&root, tmp);
		}
		else if (head->type == TOKEN_CLOSING_PARENTHESES)
			break;
		head = head->next;
	}
	return (root);
}

        // switch (head->type) {
        // case TOKEN_WORD:
		// 	new_cmd(head->value);
        //     break;
        // case TOKEN_PIPE:
        //     new_pipe(head->value);
        //     break;
        // case TOKEN_INPUT_REDIRECTION:
        //     new_in_red(head->value);
        //     break;
        // case TOKEN_OUTPUT_REDIRECTION:
        //     new_out_red(head->value);
        //     break;
        // case TOKEN_APPEND_REDIRECTION:
        //     new_append(head->value);
        //     break;
        // case TOKEN_AND:
        //     new_and(head->value);
        //     break;
        // case TOKEN_OR:
        //     new_or(head->value);
        //     break;
        // case TOKEN_OPENING_PARENTHESES:
        //     new_block(head);
        //     break;
        // default:
        //     break;            
        // }
        // if (head != NULL)
        //     head = head->next;