#include "./includes/minishell.h"

t_minishell global_minishell;

char	*ft_strdup_key(const char *s)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != '=')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i && s[j] != 0)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

t_environment	*new_env(char *key, char *value)
{
	t_environment	*v_env;

	v_env = malloc(sizeof(t_environment));
	if (!v_env)
		return (NULL);
	v_env->key = key;
	v_env->value = value;
	v_env->next = NULL;
	return (v_env);
}

void	setup_environment()
{
	int				i;
	char			*h_key;
	char			*h_value;
	t_environment	*tmp;


	h_key = ft_strdup_key((global_minishell.env)[0]);
	h_value = ft_strdup(*(global_minishell.env) + (ft_strlen(h_key) + 1));
	global_minishell.environment = new_env(h_key, h_value);
	tmp = global_minishell.environment;
	i = 1;
	while ((global_minishell.env)[i] != NULL)
	{
		h_key = ft_strdup_key(global_minishell.env[i]);
		h_value = ft_strdup(*(global_minishell.env + i) + (ft_strlen(h_key) + 1));
		tmp->next = new_env(h_key, h_value);
		tmp = tmp->next;
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
    // char *av[] = {"/usr/bin/ls", NULL};
    char *input;
    t_token *head = NULL;
    t_cmd *root;

    (void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: invalid arguments", 2);
		exit(1); 
	}
    while (1)
    {
        input = readline(PROMPT);
        if (input != NULL)
			add_history(input);
        global_minishell.env = env;
        global_minishell.line = input;
        global_minishell.root = NULL;
        head = ft_tokenize();
        setup_environment();
        global_minishell.root = build_tree(head, 0);
        // if ((global_minishell.root)->type == TOKEN_OR)
        //     printf("TOKEN_OR\n");
        // if ((global_minishell.root)->type == TOKEN_AND)
        // {
        //     printf("TOKEN_AND\n");
        //     printf("%d\n", ((l_op *)(global_minishell.root))->left->type);
        //     printf("%d\n", ((l_op *)(global_minishell.root))->right->type);
        // }
        global_minishell.main_pid = fork();
        if (!global_minishell.main_pid)
			execute();
		else
			waitpid(global_minishell.main_pid ,&(global_minishell.status), 0);
    }
    return 0;
}

    // execve("/usr/bin/ls", av,env);
    //Test Tokenizer.
    // while (head)
    // {
    //     printf (" => ");
    //     switch (head->type) {
    //     case TOKEN_WORD:
    //         printf("TOKEN_WORD {%s}\n", head->value);
    //         break;
    //     case TOKEN_PIPE:
    //         printf("TOKEN_PIPE {%s}\n", head->value);
    //         break;
    //     case TOKEN_INPUT_REDIRECTION:
    //         printf("TOKEN_INPUT_REDIRECTION {%s}\n", head->value);
    //         break;
    //     case TOKEN_OUTPUT_REDIRECTION:
    //         printf("TOKEN_OUTPUT_REDIRECTION {%s}\n", head->value);
    //         break;
    //     case TOKEN_APPEND_REDIRECTION:
    //         printf("TOKEN_APPEND_REDIRECTION {%s}\n", head->value);
    //         break;
    //     case TOKEN_HEREDOC:
    //         printf("TOKEN_HEREDOC {%s}\n", head->value);
    //         break;
    //     case TOKEN_AND:
    //         printf("TOKEN_AND {%s}\n", head->value);
    //         break;
    //     case TOKEN_OR:
    //         printf("TOKEN_OR {%s}\n", head->value);
    //         break;
    //     case TOKEN_DOUBLE_QUOTE:
    //         printf("TOKEN_DOUBLE_QUOTE {%s}\n", head->value);
    //         break;
    //     case TOKEN_SINGLE_QUOTE:
    //         printf("TOKEN_SINGLE_QUOTE {%s}\n", head->value);
    //         break;
    //     case TOKEN_VARIABLE:
    //         printf("TOKEN_VARIABLE {%s}\n", head->value);
    //         break;
    //     case TOKEN_OPENING_PARENTHESES:
    //         printf("TOKEN_OPENING_PARENTHESES {%s}\n", head->value);
    //         break;
    //     case TOKEN_CLOSING_PARENTHESES:
    //         printf("TOKEN_CLOSING_PARENTHESES {%s}\n", head->value);
    //         break;
    //     default:
    //         printf("UNKNOWN_TOKEN");
    //         break;            
    //     }
    //     head = head->next;
    // }