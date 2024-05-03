/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:19:56 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/01 15:19:58 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

t_minishell	global_minishell;

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
	int				key_len;
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
		key_len = ft_strlen(h_key) + 1;
		h_value = ft_strdup(*(global_minishell.env + i) + key_len);
		tmp->next = new_env(h_key, h_value, 0);
		tmp = tmp->next;
		i++;
	}
}

int	check_just_spaces(int flag, char **line, char *limiter)
{
	int	i;

	i = 0;
	(void)limiter;
	if (line == 0 || *line == 0)
		return (1);
	while ((*line)[i] != 0)
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n')
		{
			if (flag == 1)
				*line = ft_strdup((*line) + i);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_minishell(char *input)
{
	t_token	*head;

	head = NULL;
	global_minishell.old_stdin = dup(0);
	global_minishell.old_stdout = dup(1);
	global_minishell.pipes_nbr = 0;
	global_minishell.line = input;
	global_minishell.a_counter = 0;
	global_minishell.root = NULL;
	head = ft_tokenize();
	global_minishell.root = build_tree(head, 0);
}

int	check_single_cmd()
{
	int		flag;
	int		type;
	t_cmd	*tmp;

	type = (global_minishell.root)->type;
	if (global_minishell.root != NULL && type == TOKEN_WORD)
	{
		tmp = (t_cmd *)(global_minishell.root);
		expansion(&(tmp->args), tmp->args_number);
		flag = check_builtins((tmp->args)[0]);
		if ((flag >= 0 &&  flag <= 6))
		{
			builtins(tmp->args, flag);
			return (1);
		}
	}
	return (0);
}

void	start_execution(t_cmd *cmd)
{
	global_minishell.main_pid = fork();
	if (!global_minishell.main_pid)
	{
		check_cmd(cmd->args, global_minishell.env);
		if (execve((cmd->args)[0], cmd->args, global_minishell.env) != 0)
			exit(global_minishell.status);
	}
	else
	{
		waitpid(global_minishell.main_pid ,&(global_minishell.status), 0);
		if (WIFEXITED(global_minishell.status) != 0)
			global_minishell.status = WEXITSTATUS(global_minishell.status);
		dup2(global_minishell.old_stdin, 0);
		dup2(global_minishell.old_stdout, 1);
		// printf("--%d\n", global_minishell.status);
	}
}

void	ctr_d(char *input)
{
	if (input == NULL)
	{
		printf("exit\n");
		exit(global_minishell.status);
	}
}

int main(int argc, char **argv, char **env)
{
    char 	*input;
	int		i;

    (void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("minishell-1.0: invalid arguments", 2, '\n');
		exit(1); 
	}
    global_minishell.env = env;
	global_minishell.status = 0;
    setup_environment();
    while (1)
    {
        input = readline(PROMPT);
		ctr_d(input);
		if (check_just_spaces(1, &input, "\0") || input[0] == '\0')
			continue ;
        if (input != NULL)
			add_history(input);
        init_minishell(input);
		if (check_single_cmd() == 1)
			continue ;
		execute();
		i = 0;
		while (i++ < global_minishell.pipes_nbr)
			wait(NULL);
		// printf("%d\n", global_minishell.status);
    }
    return 0;
}
