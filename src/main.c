#include "./includes/minishell.h"

t_minishell global_minishell;

char	*ft_strdup_key(const char *s, char c)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
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

t_environment	*new_env(char *key, char *value, int flag)
{
	t_environment	*v_env;

	v_env = malloc(sizeof(t_environment));
	if (!v_env)
		return (NULL);
	v_env->key = key;
	v_env->value = value;
	v_env->flag = flag;
	v_env->next = NULL;
	return (v_env);
}

void	setup_environment()
{
	int				i;
	char			*h_key;
	char			*h_value;
	t_environment	*tmp;


	h_key = ft_strdup_key((global_minishell.env)[0], '=');
	h_value = ft_strdup(*(global_minishell.env) + (ft_strlen(h_key) + 1));
	global_minishell.environment = new_env(h_key, h_value, 0);
	tmp = global_minishell.environment;
	i = 1;
	while ((global_minishell.env)[i] != NULL)
	{
		h_key = ft_strdup_key(global_minishell.env[i], '=');
		h_value = ft_strdup(*(global_minishell.env + i) + (ft_strlen(h_key) + 1));
		tmp->next = new_env(h_key, h_value, 0);
		tmp = tmp->next;
		i++;
	}
}

int main(int argc, char **argv, char **env)
{
    l_op *tmp;
	int		flag;
    char *input;
    t_token *head = NULL;
    t_cmd *root;

    (void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell-1.0: invalid arguments", 2, '\n');
		exit(1); 
	}
    global_minishell.env = env;
    setup_environment();
    while (1)
    {
        input = readline(PROMPT);
		if (input == NULL)
		{
			printf("exit\n");
			exit(global_minishell.status);
		}
        if (input != NULL)
			add_history(input);
        global_minishell.line = input;
		global_minishell.a_counter = 0;
        global_minishell.root = NULL;
		head = ft_tokenize();
        global_minishell.root = build_tree(head, 0);
		if (global_minishell.root != NULL && (global_minishell.root)->type == TOKEN_WORD)
		{
			expansion(&(((t_cmd *)(global_minishell.root))->args), ((t_cmd *)(global_minishell.root))->args_number);
			flag = check_builtins((((t_cmd *)(global_minishell.root))->args)[0]);
			if ((flag >= 0 &&  flag <= 6))
			{
				builtins(((t_cmd *)(global_minishell.root))->args, flag);
				// printf_varibles(1);
				// exit(1);
				// t_environment	*envp;

				// envp = global_minishell.environment;
				// while (envp != NULL)
				// {
				// 	// printf("%s\n", env->key);
				// 	if(ft_strcmp(envp->key, "PWD") == 0)
				// 	{
				// 		printf("==>%s\n", envp->value);
				// 	}
				// 	envp = envp->next;
				// }
				continue ;
				// exit(global_minishell.status);
			}
		}
        global_minishell.main_pid = fork();
        if (!global_minishell.main_pid)
			execute();
		else
		{
			waitpid(global_minishell.main_pid ,&(global_minishell.status), 0);
			if (WIFEXITED(global_minishell.status) != 0)
				global_minishell.status = WEXITSTATUS(global_minishell.status);
			if (access("/tmp/heredoc", F_OK))
				unlink("/tmp/heredoc");
		}
    }
    return 0;
}