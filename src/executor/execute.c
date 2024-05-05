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
	else if (node->type == TOKEN_APPEND_REDIRECTION \
		|| node->type == TOKEN_INPUT_REDIRECTION \
		|| node->type == TOKEN_OUTPUT_REDIRECTION \
		|| node->type == TOKEN_HEREDOC)
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
