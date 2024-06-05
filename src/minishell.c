/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrac <hkarrac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:03:02 by aelbasri          #+#    #+#             */
/*   Updated: 2024/06/05 10:38:06 by hkarrac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

void	ctrl_d(char *input)
{
	if (input == NULL)
	{
		clear_garbage(&g_lobal_minishell.garbage_head);
		printf("exit\n");
		exit(g_lobal_minishell.status);
	}
}

void	close_io(void)
{
	close(g_lobal_minishell.old_stdin);
	close(g_lobal_minishell.old_stdout);
}

void	init(char ***env)
{
	g_lobal_minishell.flag1 = 0;
	g_lobal_minishell.garbage_head = NULL;
	g_lobal_minishell.garbage_head2 = NULL;
	g_lobal_minishell.env = *env;
	g_lobal_minishell.status = 0;
	setup_environment(*env, 1);
	setup_signals();
}

int	check_input(char **input)
{
	if (check_just_spaces(1, input, "\0") || (*input)[0] == '\0')
		return (1);
	if ((*input)[0] != '\0')
		add_history(*input);
	return (0);
}

int	init_minishell(char *input)
{
	g_lobal_minishell.flag2 = 0;
	g_lobal_minishell.flag3 = 0;
	g_lobal_minishell.hc = 0;
	g_lobal_minishell.pipes_nbr = 0;
	g_lobal_minishell.old_stdin = dup(0);
	g_lobal_minishell.old_stdout = dup(1);
	g_lobal_minishell.pipes_nbr = 0;
	g_lobal_minishell.line = input;
	g_lobal_minishell.a_counter = 0;
	g_lobal_minishell.root = NULL;
	g_lobal_minishell.tokens = ft_tokenize();
	if (parser(g_lobal_minishell.tokens) == 1)
	{
		clear_garbage(&g_lobal_minishell.garbage_head);
		return (1);
	}
	g_lobal_minishell.root = build_tree(g_lobal_minishell.tokens, 0);
	return (0);
}
