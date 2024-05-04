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
