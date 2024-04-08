#include "../includes/minishell.h"

t_token *ft_tokenize(void)
{
    char    *line;
    t_token *tokens_list;

    line = global_minishell.line;
    tokens_list = handle_tokens(line);

    return (tokens_list);
}