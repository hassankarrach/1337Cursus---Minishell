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

void	start_execution(t_cmd *cmd)
{
	int	flag;

	flag = check_builtins((cmd->args)[0]);
	signal(SIGINT, &my_handler2);
	signal(SIGQUIT, &my_handler2);
	g_lobal_minishell.main_pid = fork();
	if (!g_lobal_minishell.main_pid)
		exec_child(cmd, flag);
	else
	{
		waitpid(g_lobal_minishell.main_pid, &(g_lobal_minishell.status), 0);
		if (WIFEXITED(g_lobal_minishell.status) != 0)
			g_lobal_minishell.status = WEXITSTATUS(g_lobal_minishell.status);
		setup_signals();
		dup2(g_lobal_minishell.old_stdin, 0);
		dup2(g_lobal_minishell.old_stdout, 1);
	}
}

int	specify_types(t_tree *node)
{
	if (node == NULL)
	{
		recover_stdio();
		return (0);
	}
	else if (node->type == TOKEN_WORD)
		exec_cmd(node);
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node));
	else if (is_redir(node->type) == 1)
		exec_redir(node);
	else if (node->type == TOKEN_AND || node->type == TOKEN_OR)
		return (exec_and_or(node));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node));
	return (0);
}

void	execute(void)
{
	if (!(g_lobal_minishell.root))
		return ;
	specify_types(g_lobal_minishell.root);
}
