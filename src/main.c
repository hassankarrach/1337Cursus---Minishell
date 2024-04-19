#include "./includes/minishell.h"

t_minishell global_minishell;

int main(int argc, char **argv, char **env)
{
    char *input;
    input = readline(PROMPT);
    global_minishell.line = input;

    t_token *head = NULL;
    t_token *head_cpy = NULL;
    
    head = ft_tokenize();
    head_cpy = head;
    
    // Test Tokenizer.
    while (head)
    {
        switch (head->type) {
        case TOKEN_WORD:
            printf("TOKEN_WORD");
            break;
        case TOKEN_PIPE:
            printf("TOKEN_PIPE");
            break;
        case TOKEN_INPUT_REDIRECTION:
            printf("TOKEN_INPUT_REDIRECTION");
            break;
        case TOKEN_OUTPUT_REDIRECTION:
            printf("TOKEN_OUTPUT_REDIRECTION");
            break;
        case TOKEN_APPEND_REDIRECTION:
            printf("TOKEN_APPEND_REDIRECTION");
            break;
        case TOKEN_HEREDOC:
            printf("TOKEN_HEREDOC");
            break;
        case TOKEN_AND:
            printf("TOKEN_AND");
            break;
        case TOKEN_OR:
            printf("TOKEN_OR");
            break;
        case TOKEN_DOUBLE_QUOTE:
            printf("TOKEN_DOUBLE_QUOTE");
            break;
        case TOKEN_SINGLE_QUOTE:
            printf("TOKEN_SINGLE_QUOTE");
            break;
        case TOKEN_VARIABLE:
            printf("TOKEN_VARIABLE");
            break;
        case TOKEN_OPENING_PARENTHESES:
            printf("TOKEN_OPENING_PARENTHESES");
            break;
        case TOKEN_CLOSING_PARENTHESES:
            printf("TOKEN_CLOSING_PARENTHESES");
            break;
        case TOKEN_WHITE_SPACE:
            printf("TOKEN_WHITE_SPACE");
            break;
        default:
            printf("UNKNOWN_TOKEN");
            break;            
        }
        
        printf (" => ");
        head = head->next;
    }
    printf("\n\n");


    
    parser(head_cpy);
    return 0;
}
