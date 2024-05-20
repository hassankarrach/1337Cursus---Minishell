/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:33:00 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/20 17:35:18 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum tokens
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_INPUT_REDIRECTION,
	TOKEN_OUTPUT_REDIRECTION,
	TOKEN_APPEND_REDIRECTION,
	TOKEN_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_DOUBLE_QUOTE,
	TOKEN_SINGLE_QUOTE,
	TOKEN_VARIABLE,
	TOKEN_OPENING_PARENTHESES,
	TOKEN_BLOCK,
	TOKEN_CLOSING_PARENTHESES,
	TOKEN_WHITE_SPACE
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	int				is_single_quote;
	struct s_token	*next;
	struct s_token	*prev;
}	t_token;

t_token	*new_token(char *value, t_token_type type);
void	token_list_add_back(t_token **lst, t_token *new_token);
void	clear_token_list(t_token **lst);

int		is_quote(char c);
int		is_separator(char *s);
void	skip_spaces(char **line);
int		skip_quotes(char *line, size_t *i);
void	print_quote_err(char c);

t_token	*handle_tokens(char *line);

t_token	*ft_tokenize(void);

#endif