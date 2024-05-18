#include "./includes/minishell.h"

t_minishell global_minishell;

int main(int argc, char **argv, char **env)
{
	global_minishell.garbage_head = NULL;

	while (1)
	{
		//GETTING_INPUT==============
		t_token *tokens_head;
		global_minishell.line = readline(PROMPT);
		add_garbage(&global_minishell.garbage_head, new_garbage(global_minishell.line));
		//===========================

		//tokenizing=================
		tokens_head = ft_tokenize();
		global_minishell.tokens = tokens_head;
		//===========================

		//parsing.===================
		parser(global_minishell.tokens);
		//===========================
	}

	clear_garbage(&global_minishell.garbage_head);
	return 0;
}
