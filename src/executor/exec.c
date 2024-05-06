/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:42:02 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/01 15:42:05 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_block(t_tree *node)
{
	int		status;
	t_block	*block;

	status = 0;
	block = (t_block *)node;
	status = specify_types((t_tree *)block->child);
	return (status);
}

int	exec_and_or(t_tree *node)
{
	int		status;
	t_op	*and_or;

	status = 0;
	and_or = (t_op *)node;
	if (and_or->type == TOKEN_AND)
		ft_and(and_or, status);
	else if (and_or->type == TOKEN_OR)
		ft_or(and_or, status);
	return (status);
}

int	exec_pipe(t_tree *node)
{
	pid_t	id;
	t_pipe	*va_pipe;
	int		status;

	va_pipe = (t_pipe *)node;
	pipe(va_pipe->pipe_fd);
	id = fork();
	if (id == 0)
	{
		setup_in_out_fds(va_pipe->pipe_fd[0], va_pipe->pipe_fd[1], 1);
		status = specify_types((t_tree *)(va_pipe->left));
		exit(g_lobal_minishell.status);
	}
	else
	{
		if (va_pipe->index == g_lobal_minishell.pipes_nbr)
			waitpid(id, &(g_lobal_minishell.status), 0);
		setup_in_out_fds(va_pipe->pipe_fd[1], va_pipe->pipe_fd[0], 0);
		status = specify_types((t_tree *)(va_pipe->right));
		wait_loop();
	}
	return (status);
}

void	exec_cmd(t_tree *node)
{
	t_cmd	*cmd;
	int		flag;

	cmd = (t_cmd *)node;
	if ((g_lobal_minishell.root)->type != TOKEN_WORD)
		expansion(&(cmd->args), cmd->args_number);
	flag = check_builtins((cmd->args)[0]);
	if (flag >= 0 && flag <= 6)
		builtins(cmd->args, flag);
	else
		start_execution(cmd);
}

void	start_execution(t_cmd *cmd)
{
	g_lobal_minishell.main_pid = fork();
	if (!g_lobal_minishell.main_pid)
	{
		if ((cmd->args)[0] == NULL)
			exit(0);
		check_cmd(cmd->args, g_lobal_minishell.env);
		if (execve((cmd->args)[0], cmd->args, g_lobal_minishell.env) != 0)
			exit(g_lobal_minishell.status);
	}
	else
	{
		waitpid(g_lobal_minishell.main_pid, &(g_lobal_minishell.status), 0);
		if (WIFEXITED(g_lobal_minishell.status) != 0)
			g_lobal_minishell.status = WEXITSTATUS(g_lobal_minishell.status);
		dup2(g_lobal_minishell.old_stdin, 0);
		dup2(g_lobal_minishell.old_stdout, 1);
	}
}
