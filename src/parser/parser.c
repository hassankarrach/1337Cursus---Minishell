/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:52:32 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/23 15:57:02 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	is_valid_parentheses(t_token *list)
{
	int	count;

	count = 0;
	while (list)
	{
		if (list->type == TOKEN_OPENING_PARENTHESES)
			count++;
		else if (list->type == TOKEN_CLOSING_PARENTHESES)
		{
			if (count == 0)
				return (0);
			count--;
		}
		if (count < 0)
			return (0);
		list = list->next;
	}
	return (count == 0);
}

int	parser(t_token *tokens)
{
	int	is_syntax_err;

	is_syntax_err = 0;
	if (!is_valid_parentheses(tokens) && print_syntax_error())
		return (1);
	while (tokens)
	{
		if (tokens->type == TOKEN_APPEND_REDIRECTION
			|| tokens->type == TOKEN_HEREDOC
			|| tokens->type == TOKEN_OUTPUT_REDIRECTION
			|| tokens->type == TOKEN_INPUT_REDIRECTION)
			is_syntax_err = check_syntax_redirections(tokens);
		else if (tokens->type == TOKEN_PIPE 
			|| tokens->type == TOKEN_AND || tokens->type == TOKEN_OR)
			is_syntax_err = check_syntax_and_or_pipe(tokens);
		else if (tokens->type == TOKEN_OPENING_PARENTHESES)
			is_syntax_err = check_syntax_open_parentheses(tokens);
		else if (tokens->type == TOKEN_CLOSING_PARENTHESES)
			is_syntax_err = check_syntax_close_parentheses(tokens);
		if (is_syntax_err)
		{
			ft_putstr_fd("minishell error : syntax error.", 2, '\n');
			return (1);
		}
		tokens = tokens->next;
	}
	return (0);
}
