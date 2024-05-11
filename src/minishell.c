/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:03:02 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/04 17:03:05 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int	check_single_cmd(int flag)
{
	t_cmd	*tmp;

	if (g_lobal_minishell.root != NULL && \
		(g_lobal_minishell.root)->type == TOKEN_WORD)
	{
		tmp = (t_cmd *)(g_lobal_minishell.root);
		expansion(&(tmp->args), tmp->args_number);
		// printf("%s\n", (tmp->args)[1]);
		flag = check_builtins((tmp->args)[0]);
		if ((flag >= 0 && flag <= 6))
		{
			builtins(tmp->args, flag);
			return (1);
		}
	}
	return (0);
}

void	close_io(void)
{
	close(g_lobal_minishell.old_stdin);
	close(g_lobal_minishell.old_stdout);
}

void	init(char ***env)
{
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

void	init_minishell(char *input)
{
	t_token	*head;

	head = NULL;
	g_lobal_minishell.flag2 = 0;
	g_lobal_minishell.flag3 = 0;
	g_lobal_minishell.pipes_nbr = 0;
	g_lobal_minishell.old_stdin = dup(0);
	g_lobal_minishell.old_stdout = dup(1);
	g_lobal_minishell.pipes_nbr = 0;
	g_lobal_minishell.line = input;
	g_lobal_minishell.a_counter = 0;
	g_lobal_minishell.root = NULL;
	head = ft_tokenize();
	g_lobal_minishell.root = build_tree(head, 0);
}
