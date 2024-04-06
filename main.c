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
// create new line without spaces at the beginning
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

t_line	*new_line(void *component)
{
	t_line	*node;

	node = malloc(sizeof(t_line));
	if (!node)
		return (NULL);
	node->component = component;
	node->next = NULL;
	return (node);
}
// Duplicate parts of string using start and end (this function  can help you to split a string wit different separators just you have to know teh start and the end )
char	*ft_strdup_parts(const char *s, int start, int end)
{
	char	*str;
	size_t	i;
	size_t	j;

	if (s == NULL)
		return (NULL);
	str = (char *)malloc(((end - start) + 2) * sizeof(char));
	if (!str)
		return (NULL);
	j = 0;
	i = (end - start) + 1;
	while (i > j && s[j] != '\0')
	{
		str[j] = s[start];
		start++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
// create a linked list to split commands with pipe (you can add && and || ) 
void	setup_to_parse(char *line, t_data *data)
{
	int	i;
	int	flag;
	int	start;
	t_line	*v_line;

	flag = 0;
	i = 0;
	start = 0;
	data->line = NULL;
	while (line[i])
	{
		if(line[i] == '\"' || line[i] == '\'')
		{
			flag++;
			if (flag == 2)
				flag = 0;
		}
		if (flag == 0 && line[i] == '|')
		{
			if (data->line == 0)
			{
				data->line = new_line(ft_strdup_parts(line, start, i - 1));
				start = i + 1;
				v_line = data->line;
			}
			else
			{
				v_line->next = new_line(ft_strdup_parts(line, start, i - 1));
				start = i + 1;
				v_line = v_line->next;
			}
		}
		i++;
	}
	if (data->line == NULL)
		data->line = new_line(ft_strdup_parts(line, start, i - 1));
	else
		v_line->next = new_line(ft_strdup_parts(line, start, i - 1));

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
		if (check_just_spaces(1, &line, "\0") || line[0] == '\0')
			continue ;
		if (line != NULL)
			add_history(line);
		if (parse(line, &data) == 0)
		{
			_error(data.error);
			continue;
		}
		setup_to_parse(line, &data);
		execute(data);
		// printf("%s", line);
	}
}
