#include "../includes/minishell.h"

static int append_seperator(token_type type, char **line_ptr, t_token **tokens_list) //test this func alone
{
    t_token *token;

    token = new_token(NULL, type);
    if (!token)
        return (0);
    token_list_add_back(tokens_list, token);
    (*line_ptr)++;
    if (type == TOKEN_AND || type == TOKEN_OR || type == TOKEN_APPEND_REDIRECTION || type == TOKEN_HEREDOC)
        (*line_ptr)++;
    return (1);
}

static int append_identifier(char **line_ptr, t_token **tokens_list)
{
    char    *tmp;
    char    *value;
    t_token *token;
    size_t  i;

    tmp = (*line_ptr);
    i = 0;

    while (tmp[i] && !is_separator(tmp + i))
    {
        if (is_quote(tmp[i]))
        {
            if (!skip_quotes(tmp, &i))
            {
                print_quote_err(tmp[i]);
                return (0);
            }
        }
        else
            i++;
    }
    value = ft_substr(tmp, 0, i); //TB free.
    if (!value)
        return (0);
    token = new_token(value, TOKEN_WORD);
    if (!token)
        return (0);
    (*line_ptr) += i;
    token_list_add_back(tokens_list, token);
    return (1);
}

static int	handle_separator(char **line_ptr, t_token **tokens_list)
{
	if (!ft_strncmp(*line_ptr, "<<", 2))
    	return (append_seperator(TOKEN_HEREDOC, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">>", 2))
		return (append_seperator(TOKEN_APPEND_REDIRECTION, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "<", 1))
        return (append_seperator(TOKEN_INPUT_REDIRECTION, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ">", 1))
		return (append_seperator(TOKEN_OUTPUT_REDIRECTION, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "(", 1))
		return (append_seperator(TOKEN_OPENING_PARENTHESES, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, ")", 1))
		return (append_seperator(TOKEN_CLOSING_PARENTHESES, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "&&", 2))
		return (append_seperator(TOKEN_AND, line_ptr, tokens_list) && 1);
	else if (!ft_strncmp(*line_ptr, "||", 2))
		return (append_seperator(TOKEN_OR, line_ptr, tokens_list) && 1);
	else
		return (append_seperator(TOKEN_PIPE, line_ptr, tokens_list) && 1);
}

t_token *handle_tokens(char *line)
{
    int     is_err;
    t_token *tokens_list;

    is_err = 0;
    tokens_list = NULL;

    while (*line)
    {
        if (is_err)
            return (NULL);
        if (ft_is_space(*line))
            skip_spaces(&line);
        else if (ft_strncmp(line, "<", 1) == 0 || ft_strncmp(line, ">", 1) == 0
            || ft_strncmp(line, "|", 1) == 0 || ft_strncmp(line, "&&", 2) == 0
            || ft_strncmp(line, "(", 1) == 0 || ft_strncmp(line, ")", 1) == 0)
            is_err = (!handle_separator(&line, &tokens_list) && 1);
        else
            is_err = (!append_identifier(&line, &tokens_list) && 1);
    }
    return (tokens_list);
}