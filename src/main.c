#include "./includes/minishell.h"

t_minishell global_minishell;

void    print_tokens(t_token *head)
{
	// Test Tokenizer.
	while (head)
	{
		switch (head->type) {
		case TOKEN_WORD:
			printf("TOKEN_WORD[%s]", head->value);
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
}

int main(int argc, char **argv, char **env)
{
	global_minishell.garbage_head = NULL;

	while (1)
	{
		//GETTING_INPUT==============
		t_token *tokens_head;
		global_minishell.line = readline(PROMPT);
		add_garbage(&global_minishell.garbage_head, new_garbage(global_minishell.line, ptr_garbage));
		if (strcmp(global_minishell.line, "end") == 0)
			break;
		//===========================

		//tokenizing=================
		tokens_head = ft_tokenize();
		global_minishell.tokens = tokens_head;
		print_tokens(tokens_head);
		//===========================

		//parsing.===================
		// parser(global_minishell.tokens);
		//===========================
	}


	int i = 0;
	while (global_minishell.garbage_head)
	{
		i++;
		global_minishell.garbage_head = global_minishell.garbage_head->next;
	}
	printf("==%d==\n", i);
	return 0;
}
