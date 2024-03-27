/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 09:46:02 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/08 09:46:08 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quotes(char *line, t_data *data)
{
	int	j;
	int	k;
	int	i;

	i = 0;
	j = 0;
	k = 0;
	while (line[i] != 0)
	{
		if (line[i] == '\"' && k == 0)
			j++;
		if (j == 2)
			j = 0;
		if(line[i] == '\'' && j == 0)
			k++;
		if (k == 2)
			k = 0;
		i++;
	}
	if (j != 0 || k != 0)
	{
		data->error = 0;
		return (0);
	}
	return (1);
}

int	check_logical_symboles(char *line, t_data *data, char *token)
{
	int	len;
	int	i;

	i = 0;
	len = ft_strlen(token);
	if (ft_strncmp((line + i), token, len) == 0)
	{
		data->error = 3;
		return (0); 
	}
	while (line[i] != '\0')
	{
		if (ft_strncmp((line + i), token, ft_strlen(token)) == 0)
		{
			if (check_just_spaces(0, (&line + i + len), token) == 1)
			{
				data->error = 4;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_pipe(char *line, t_data *data)
{
	int		i;
	char	*_line;

	i = 0;
	if (line[i] == '|' && line[i + 1] != '|')
	{
		data->error = 1;
		return (0); 
	}
	while (line[i] != '\0')
	{
		if (line[i] == '|' && line[i + 1] != '|' && line[i - 1] != '|')
		{
			_line = line + i;
			if (check_just_spaces(0, &_line, "|") == 1 || line[i + 1] == '\0')
			{
				data->error = 2;
				return (0);
			}
		}
		i++;
	}
	return (1) ;
}

int	parse(char *line, t_data *data)
{
	if (check_quotes(line, data) == 0)
		return (0);
	if (check_pipe(line, data) == 0)
		return (0);
	if (check_logical_symboles(line, data, "&&") == 0)
		return (0);
	if (check_logical_symboles(line, data, "||") == 0)
		return (0);
	return (1);
}
