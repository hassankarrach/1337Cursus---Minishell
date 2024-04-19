#include "../includes/minishell.h"

static void syntax_error(char *token)
{
    ft_putstr_fd("minishell error : syntax error `", 2);
    ft_putstr_fd(token, 2);
    ft_putstr_fd("\n", 2);
    return ;
}

static void check_redirections_errors(t_token *redir_token)
{
    printf("entered\n");
    if (redir_token->next->type == TOKEN_PIPE)
        syntax_error("|");
}

void parser(t_token *tokens)
{
    t_token *head = tokens;
    while (head)
    {
        printf("reachs\n");
        if (head->type == TOKEN_APPEND_REDIRECTION 
            || head->type == TOKEN_HEREDOC
            || head->type == TOKEN_OUTPUT_REDIRECTION
            || head->type == TOKEN_INPUT_REDIRECTION)
            check_redirections_errors(head);
        head = head->next;
    }
}