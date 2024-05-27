/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zero <zero@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 15:54:41 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/27 10:25:28 by zero             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_syntax_error(void)
{
	ft_putstr_fd("minishell error : syntax error.", 2, '\n');
	return (1);
}

int	check_syntax_and_or_pipe(t_token *curr_token)
{
	t_token	*right;
	t_token	*left;

	right = curr_token;
	left = curr_token;
	while (right->next && right->next->type == TOKEN_WHITE_SPACE)
		right = right->next;
	while (left->prev && left->prev->type == TOKEN_WHITE_SPACE)
		left = left->prev;
	if ((left->prev && (left->prev->type != TOKEN_SINGLE_QUOTE
				&& left->prev->type != TOKEN_DOUBLE_QUOTE
				&& left->prev->type != TOKEN_CLOSING_PARENTHESES
				&& left->prev->type != TOKEN_WORD)) || !left->prev)
	{
		printf("reachs 1\n");
		return (1);
	}
	if ((right->next && (right->next->type != TOKEN_SINGLE_QUOTE
				&& right->next->type != TOKEN_DOUBLE_QUOTE
				&& right->next->type != TOKEN_HEREDOC
				&& right->next->type != TOKEN_APPEND_REDIRECTION
				&& right->next->type != TOKEN_INPUT_REDIRECTION
				&& right->next->type != TOKEN_OUTPUT_REDIRECTION
				&& right->next->type != TOKEN_OPENING_PARENTHESES
				&& right->next->type != TOKEN_WORD)) || !right->next)
	{
		printf("reachs 2\n");
		return (1);
	}
	return (0);
}

int	check_syntax_redirections(t_token *curr_token)
{
	while (curr_token->next && curr_token->next->type == TOKEN_WHITE_SPACE)
		curr_token = curr_token->next;
	if (curr_token->next && (curr_token->next->type != TOKEN_SINGLE_QUOTE
			&& curr_token->next->type != TOKEN_DOUBLE_QUOTE
			&& curr_token->next->type != TOKEN_WORD))
		return (1);
	return (0);
}

int	check_syntax_open_parentheses(t_token *curr_token)
{
	t_token	*right;
	t_token	*left;

	right = curr_token;
	left = curr_token;
	while (right->next && right->next->type == TOKEN_WHITE_SPACE)
		right = right->next;
	while (left->prev && left->prev->type == TOKEN_WHITE_SPACE)
		left = left->prev;
	if (right->next && (right->next->type != TOKEN_SINGLE_QUOTE
			&& right->next->type != TOKEN_DOUBLE_QUOTE
			&& right->next->type != TOKEN_WORD
			&& right->next->type != TOKEN_HEREDOC
			&& right->next->type != TOKEN_APPEND_REDIRECTION
			&& right->next->type != TOKEN_INPUT_REDIRECTION
			&& right->next->type != TOKEN_OUTPUT_REDIRECTION
			&& right->next->type != TOKEN_OPENING_PARENTHESES))
	{
		printf("reachs 3\n");
		return (1);
	}
	if (left->prev && (left->prev->type != TOKEN_AND
			&& left->prev->type != TOKEN_OR
			&& left->prev->type != TOKEN_PIPE
			&& left->prev->type != TOKEN_OPENING_PARENTHESES))
	{
		printf("reachs 4\n");
		return (1);
	}
	return (0);
}

int	check_syntax_close_parentheses(t_token *curr_token)
{
	t_token	*right;
	t_token	*left;

	right = curr_token;
	left = curr_token;
	while (right->next && right->next->type == TOKEN_WHITE_SPACE)
		right = right->next;
	while (left->prev && left->prev->type == TOKEN_WHITE_SPACE)
		left = left->prev;
	if (right->next && (right->next->type != TOKEN_AND
			&& right->next->type != TOKEN_OR
			&& right->next->type != TOKEN_PIPE
			&& right->next->type != TOKEN_CLOSING_PARENTHESES
			&& right->next->type != TOKEN_APPEND_REDIRECTION
			&& right->next->type != TOKEN_OUTPUT_REDIRECTION))
	{
		printf("reachs 5\n");
		return (1);
	}
	if (left->prev && (left->prev->type != TOKEN_SINGLE_QUOTE
			&& left->prev->type != TOKEN_DOUBLE_QUOTE
			&& left->prev->type != TOKEN_WORD
			&& left->prev->type != TOKEN_CLOSING_PARENTHESES))
	{
		printf("reachs 6\n");
		return (1);
	}
	return (0);
}
