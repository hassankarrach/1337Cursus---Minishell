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

void	init_minishell(char *input)
{
	t_token	*head;

	head = NULL;
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
