#include "../includes/minishell.h"

int is_quote(char c)
{
    if (c == '\'' || c == '"')
        return (1);
    return (0);
}

int is_separator(char *s)
{
    if (!ft_strncmp(s, "&&", 2) || *s == ' ' || *s == '\t' || *s == '<'
        || *s == '<' || *s == '|' || *s == '(' || *s == ')')
        return (1);
    return (0);
}

void skip_spaces(char **line)
{
    while (**line && ft_is_space(**line))
        (*line)++;
}

int skip_quotes(char *line, size_t *i)
{
    char quote;

    quote = line[*i];
    if (ft_strchr(line + (*i + 1), quote))
    {
        (*i)++;
        while (line[*i] != quote)
            (*i)++;
        (*i)++;
        return (1);
    }
    return (0);
}

void	print_quote_err(char c)
{
	ft_putstr_fd("minishell error : unclosed `", 2, 4);
	write(2, &c, 1);
	ft_putstr_fd("'", 2, '\n');
}