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

int	check_just_spaces(char *line)
{
	while (*line)
	{
		if (*line != ' ' && *line == '\t' && *line == '\n')
			return (0)
		line++;
	}
	return (1);
}

int	count_env(char **env)
{
	int	i;

	i == 0;
	while (env[i] != NULL)
		i++;
	return (i);
}

void	setup_environment(char **env, t_data *data)
{
	int		i;
	int		j;
	char	len;

	data->my_env = (char **)malloc((count_env + 1) * sizeof(char *));
	if (!data->env)
	{
		ft_putstr_fd("\033[1;31mmalloc_error : setup environment \033[0m", 2);
		exit(1);
	}
	i = 0;
	while  (env[i])
	{
		j = 0;
		len = ft_strlen();
		while (env[i][j] != 0)
		{
			data =
			j++;
		}
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	 data;
	char	*line;

	while (1)
	{
		data = (t_data){0};
		setup_environment(env, data);
		line = readline("\033[1;32m > myMiniSh-1.0$ \033[0m");
		if (!line || check_just_spaces(line) || line[0] == '\0')
			continue ;
		if (line != NULL)
			add_history(line);
		// printf("%s", line);
		// parse(line, &data);
	}
}
