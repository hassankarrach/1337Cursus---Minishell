#ifndef TOKENIZER_H
# define TOKENIZER_H

# define PROMPT "\033[1;32m > minishell-1.0$ \033[0m "

typedef enum tokens{
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
    TOKEN_CLOSING_PARENTHESES
}               token_type;

typedef struct s_token{
    token_type  type;
    char        *value;
    struct s_token  *next;
    struct s_token  *prev; 
}   t_token;


//linked_list_utils
t_token *new_token(char *value, token_type type);
void	token_list_add_back(t_token **lst, t_token *new_token);
void    clear_token_list(t_token **lst);

//tokenizer_utils
int     is_quote(char c);
int     is_separator(char *s);
void    skip_spaces(char **line);
int     skip_quotes(char *line, size_t *i);
void    print_quote_err(char c);

//handlers
t_token *handle_tokens(char *line);

//tokenizer
t_token *ft_tokenize(void);

#endif