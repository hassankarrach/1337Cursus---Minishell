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

void	my_handler5(int i)
{
	(void)i;
	recover_stdio();
	rl_on_new_line();
	rl_replace_line("", 0);
}

void	copy_env(char ***env)
{
	t_environment	*tmp;
	char			*tmp1;
	int				j;

	j = 0;
	g_lobal_minishell.flag1 = 1;
	tmp = g_lobal_minishell.environment;
	while (tmp != NULL)
	{
		tmp1 = ft_strjoin(tmp->key, "=");
		(*env)[j] = ft_strjoin(tmp1, tmp->value);
		add_garbage(&g_lobal_minishell.garbage_head2, new_garbage((*env)[j]));
		add_garbage(&g_lobal_minishell.garbage_head2, new_garbage(tmp1));
		tmp = tmp->next;
		j++;
	}
	(*env)[j] = NULL;
}

void	start_execution(t_cmd *cmd)
{
	int	flag;

	flag = check_builtins((cmd->args)[0]);
	signal(SIGINT, &my_handler2);
	signal(SIGQUIT, &my_handler4);
	g_lobal_minishell.main_pid = fork();
	if (!g_lobal_minishell.main_pid)
		exec_child(cmd, flag);
	else
	{
		waitpid(g_lobal_minishell.main_pid, &(g_lobal_minishell.status), 0);
		if (WIFEXITED(g_lobal_minishell.status) != 0)
			g_lobal_minishell.status = WEXITSTATUS(g_lobal_minishell.status);
		else if (WIFSIGNALED(g_lobal_minishell.status))
			g_lobal_minishell.status = WTERMSIG(g_lobal_minishell.status) + 128;
		dup2(g_lobal_minishell.old_stdin, 0);
		if (g_lobal_minishell.flag3 != 1)
			dup2(g_lobal_minishell.old_stdout, 1);
		signal(SIGQUIT, &my_handler5);
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
