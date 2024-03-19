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

void	setup_environment(char **envp, t_data *data)
{
	t_environment	*env;
	

	env = malloc(sizeof(t_environment));
	while (envp[i])
	{}
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

int	main(int ac, char **av, char **env)
{
	t_data	 data;
	char	*line;

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
		// tokenizer(linr, &data);
		if (parse(line, &data) == 0)
		{
			_error(data.error);
			continue;
		}
		execute(data);
		// printf("%s", line);
	}
}
