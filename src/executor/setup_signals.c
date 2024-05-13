/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setup_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 09:52:39 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/10 09:52:43 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ctrl_d(char *input)
{
	if (input == NULL)
	{
		printf("exit\n");
		exit(g_lobal_minishell.status);
	}
}

void	my_handler(int i)
{
	(void)i;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	g_lobal_minishell.status = 130;
}

void	my_handler3(int i)
{
	(void)i;
	write(1, "\n", 1);
	g_lobal_minishell.hc = 1;
	g_lobal_minishell.status = 130;
	close(0);
}

void	my_handler2(int i)
{
	(void)i;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_lobal_minishell.status = 130;
}

void	setup_signals(void)
{
	signal(SIGINT, &my_handler);
	signal(SIGQUIT, SIG_IGN);
}
