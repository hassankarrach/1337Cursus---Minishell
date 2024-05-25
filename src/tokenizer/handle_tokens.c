/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 15:36:40 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/25 11:18:35 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	append_sep(t_token_type type, char **line_ptr,
	t_token **tokens_list)
{
	t_token	*token;

	token = new_token(NULL, type);
	if (!token)
		return (0);
	token_list_add_back(tokens_list, token);
	(*line_ptr)++;
	if (type == TOKEN_AND || type == TOKEN_OR
		|| type == TOKEN_APPEND_REDIRECTION || type == TOKEN_HEREDOC)
		(*line_ptr)++;
	if (type == TOKEN_WHITE_SPACE)
		skip_spaces(line_ptr);
	return (1);
}

static int	creat_identifier_node(char *value, t_token **tokens_list)
{
	t_token	*token;
	
	if (is_containing_asterisk(value))
	{
		handle_expand_asterisk_wildcard(tokens_list, value);
		return (1);
	}
	token = new_token(value, TOKEN_WORD);
	if (*value == '\'')
		token->is_single_quote = 1;
	if (!token)
		return (0);
	token_list_add_back(tokens_list, token);
	return (1);
}

static int	append_identifier(char **line_ptr, t_token **tokens_list)
{
	char	*tmp;
	char	*value;
	size_t	i;

	tmp = (*line_ptr);
	i = 0;
	while (tmp[i] && !is_separator(tmp + i))
	{
		if (is_quote(tmp[i]))
		{
			if (!skip_quotes(tmp, &i))
				return (print_quote_err(tmp[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp, 0, i);

	if (!value)
		return (0);
	(*line_ptr) += i;
	return (creat_identifier_node(value, tokens_list));
}

static int	handle_separator(char **line_ptr, t_token **tokens_list)
{
	if (ft_is_space(**line_ptr))
		return (append_sep(TOKEN_WHITE_SPACE,
				line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<<", 2))
		return (append_sep(TOKEN_HEREDOC, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (append_sep(TOKEN_APPEND_REDIRECTION,
				line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
		return (append_sep(TOKEN_INPUT_REDIRECTION,
				line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (append_sep(TOKEN_OUTPUT_REDIRECTION,
				line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "(", 1))
		return (append_sep(TOKEN_OPENING_PARENTHESES,
				line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ")", 1))
		return (append_sep(TOKEN_CLOSING_PARENTHESES, line_ptr, tokens_list));
	else if (!ft_strncmp(*line_ptr, "&&", 2))
		return (append_sep(TOKEN_AND, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "||", 2))
		return (append_sep(TOKEN_OR, line_ptr, tokens_list) && 1);
	else
		return (append_sep(TOKEN_PIPE, line_ptr, tokens_list) && 1);
}

t_token	*handle_tokens(char *line)
{
	int		is_err;
	t_token	*tokens_list;

	is_err = 0;
	tokens_list = NULL;
	while (*line)
	{
		if (is_err)
			return (NULL);
		if (ft_strncmp(line, "<", 1) == 0
			|| ft_strncmp(line, ">", 1) == 0 || ft_is_space(*line)
			|| ft_strncmp(line, "|", 1) == 0 || ft_strncmp(line, "&&", 2) == 0
			|| ft_strncmp(line, "(", 1) == 0 || ft_strncmp(line, ")", 1) == 0)
			is_err = (!handle_separator(&line, &tokens_list) && 1);
		else
			is_err = (!append_identifier(&line, &tokens_list) && 1);
	}
	return (tokens_list);
}
