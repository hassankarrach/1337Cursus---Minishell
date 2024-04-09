/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:59:38 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/09 15:59:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_block(t_tree *node)
{
	int		status;
	t_block	*block;
	pid_t	id;

	block = (t_block *)node;
	id = fork();
	if (id == 0)
		status = specify_types((t_tree *)block->child);
	else
		waitpid(id, &status, 0);
	return(status);
}

static int	exec_and_or(t_tree *node)
{
	int	status;
	int id;
	l_op *and_or;

	and_or = (l_op *)node;
	if (and_or->type == TOKEN_AND)
	{
		id = fork();
		if (id == 0)
			status = specify_types((t_tree *)and_or->left);
		else
		{
			waitpid(id, &status, 0);
			if (status == 0)
				status = specify_types((t_tree *)and_or->right);
		}
	}
	else if (and_or->type == TOKEN_OR)
	{
		id = fork();
		if (id == 0)
			status = specify_types((t_tree *)and_or->left);
		else
		{
			waitpid(id, &status, 0);
			if (status != 0)
				status = specify_types((t_tree *)and_or->right);
		}
	}
	return (status);
}

static int	exec_pipe(t_tree *node)
{
	pid_t	id;
	t_pipe	*va_pipe;
	int		status;

	va_pipe = (t_pipe *)node;
	pipe(va_pipe->pipe_fd);
	id = fork();
	if (id == 0)
	{
		dup2(va_pipe->pipe_fd[1], 1);
		status = specify_types((t_tree *)va_pipe->left);
	}
	else
	{
		waitpid(id, &status,0);
		dup2(va_pipe->pipe_fd[0], 0);
		status = specify_types((t_tree *)va_pipe->right);
	}
	return(status);
}

static void	exec_cmd(t_tree *node)
{
	int		status;
	t_cmd	*cmd;
	
	cmd = (t_cmd *)node;
	check_cmd(cmd->args, cmd->env);
	execve((cmd->args)[0], cmd->args, cmd->env);
}

static void	exec_redir(t_tree *node)
{
	t_redir *redir;

	redir = (t_redir *)node;
	if (redir->type == TOKEN_INPUT_REDIRECTION)
	{
		close(0);
		open(redir->file_name, O_RDONLY);
	}
	else
	{
		close(1);
		open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
}

int	specify_types(t_tree *node)
{
	if (node->type == TOKEN_WORD)
		exec_cmd(node);
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node));
	else if (node->type == TOKEN_INPUT_REDIRECTION || node->type == TOKEN_OUTPUT_REDIRECTION)
		exec_redir(node);
	else if (node->type ==  TOKEN_AND || node->type == TOKEN_OR)
		return (exec_and_or(node));
	else if (node->type == TOKEN_OPENING_PARENTHESES)
		return (exec_block(node));
	return (0);
}

void	execute()
{
	if (!(global_minishell.root))
		return ;
	global_minishell.status = specify_types(global_minishell.root);
}
