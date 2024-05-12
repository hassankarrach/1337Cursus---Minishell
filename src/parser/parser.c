#include "../includes/minishell.h"

static int check_syntax_redirections(t_token *curr_token)
{
    while (curr_token->next && curr_token->next->type == TOKEN_WHITE_SPACE)
        curr_token = curr_token->next;
    if (curr_token->next && (curr_token->next->type == TOKEN_PIPE
    || curr_token->next->type == TOKEN_CLOSING_PARENTHESES
    || curr_token->next->type == TOKEN_OPENING_PARENTHESES
    || curr_token->next->type == TOKEN_APPEND_REDIRECTION
    || curr_token->next->type == TOKEN_HEREDOC
    || curr_token->next->type == TOKEN_INPUT_REDIRECTION
    || curr_token->next->type == TOKEN_OUTPUT_REDIRECTION))
        return (1);
    else if (!curr_token->next)
        return (1);
    return (0);
}

static int check_syntax_pipe(t_token *curr_token)
{
    while (curr_token->next && curr_token->next->type == TOKEN_WHITE_SPACE)
        curr_token = curr_token->next;
    if (curr_token->next && curr_token->next->type == TOKEN_PIPE)
        return (1);
    return (0);
}

void parser(t_token *tokens)
{
    int is_syntax_err;
    int parenthesis_syntax;

    is_syntax_err = 0;
    parenthesis_syntax = -1;
    while (tokens)
    {
        //Parenthesis_parse.
        if (tokens->type == TOKEN_OPENING_PARENTHESES)
            parenthesis_syntax++;
        else if (tokens->type == TOKEN_CLOSING_PARENTHESES)
            parenthesis_syntax--;
        // 💀 few parsing cases, needs to be addressed. ⏳
        // if (parenthesis_syntax == -1)
        //     is_syntax_err = 1;

        if (tokens->type == TOKEN_APPEND_REDIRECTION 
            || tokens->type == TOKEN_HEREDOC
            || tokens->type == TOKEN_OUTPUT_REDIRECTION
            || tokens->type == TOKEN_INPUT_REDIRECTION)
            is_syntax_err = check_syntax_redirections(tokens);
        else if (tokens->type == TOKEN_PIPE)
            is_syntax_err = check_syntax_pipe(tokens);
        if (is_syntax_err)
        {
            ft_putstr_fd("minishell error : syntax error.", 2);
            return ;
        }
        tokens = tokens->next;
    }
}