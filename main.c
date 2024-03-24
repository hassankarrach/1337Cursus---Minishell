/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 12:29:39 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/08 12:29:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_just_spaces(char *line, char *limiter)
{
	int	i;

	i = 0;
	(void)limiter;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
			return (0);
		line++;
	}
	return (1);
}

int	count_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	return (i);
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

void	setup_environment(char **envp, t_data *data)
{
	int				i;
	char			*h_key;
	char			*h_value;
	t_environment	*tmp;


	h_key = ft_strdup_key(envp[0]);
	h_value = ft_strdup(*(envp) + (ft_strlen(h_key) + 1));
	data->environment = new_env(h_key, h_value);
	tmp = data->environment;
	i = 1;
	while (envp[i] != NULL)
	{
		h_key = ft_strdup_key(envp[i]);
		h_value = ft_strdup(*(envp + i) + (ft_strlen(h_key) + 1));
		tmp->next = new_env(h_key, h_value);
		tmp = tmp->next;
		i++;
	}
}

// ft_putstr_fd("\033[1;31mError: malloc: setup environment \033[0m", 2);
// 		exit(1);

void	_error(int	i)
{
	if (i == 0)
		ft_putstr_fd("Error: unclosed quote", 2);
	else if (i == 1)
		ft_putstr_fd("Error: syntax error near unexpected token '|'", 2);
	else if (i == 2)
		ft_putstr_fd("Error: unclosed pipe", 2);
	else if (i == 3)
		ft_putstr_fd("Error: syntax error near unexpected token '||' or '&&'", 2);
	else if (i == 4)
		ft_putstr_fd("Error: unclosed token", 2);
}
char	**ft_split_operators(char *line, t_data *data)
{
	
}

/* Tree implementation */
void	grass(char *line, t_data *data)
{
	t_tree	*root;

	root = data->root;
		 
}

int	main(int ac, char **av, char **env)
{
	t_data	 data;
	char	*line;
	t_environment *tmp;

	(void)av;
	if (ac != 1)
	{
		ft_putstr_fd("Error: invalid arguments", 2);
		exit(1); 
	}
	while (1)
	{
		data = (t_data){0};
		setup_environment(env, &data);
		line = readline("\033[1;32m > myMiniSh-1.0$ \033[0m");
		if (line == NULL)
			exit(0);
		if (check_just_spaces(line, "\0") == 1 || line[0] == '\0')
			continue ;
		if (line != NULL)
			add_history(line);
		if (parse(line, &data) == 0)
		{
			_error(data.error);
			continue;
		}
		grass(line, data);
		// execute(data);
		// printf("%s", line);
	}
}
