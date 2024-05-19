/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:19:56 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/01 15:19:58 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell	g_lobal_minishell;

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell-1.0: invalid arguments", 2, '\n');
		exit(1);
	}
	init(&env);
	while (1)
	{
		input = readline(PROMPT);
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(g_lobal_minishell.line));
		ctrl_d(input);
		if (check_input(&input) == 1)
			continue ;
		if (init_minishell(input) == 1)
			continue ;
		if (g_lobal_minishell.hc == 1)
		{
			close_io();
			continue ;
		}
		execute();
		close_io();
		clear_garbage(&g_lobal_minishell.garbage_head);
		unlink("/tmp/.buffer");
	}
}
