/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:19:56 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/24 18:18:31 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell	g_lobal_minishell;

void    print_tokens()
{
	t_token *head = NULL;
	// head = ft_tokenize();
	head = g_lobal_minishell.tokens;

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
	printf("\n");
}

static void	check_argc_minishell(int argc)
{
	if (argc != 1)
	{
		ft_putstr_fd("minishell-1.0: invalid arguments", 2, '\n');
		exit(1);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*input;

	(void)argv;
	check_argc_minishell(argc);
	init(&env);
	while (1)
	{
		input = readline(PROMPT);
		ctrl_d(input);
		if (check_input(&input) == 1)
			continue ;
		if (init_minishell(input) == 1)
			continue ;
		if (g_lobal_minishell.hc == 1)
		{
			close_io();
			continue ;
		}
		// print_tokens();
		execute();
		close_io();
		clear_garbage(&g_lobal_minishell.garbage_head);
		unlink("/tmp/.heredocbuffer");
	}
}
