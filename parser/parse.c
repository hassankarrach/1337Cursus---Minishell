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

int	check_quotes(char *line, int i, t_data *data)
{
	int	j;
	int	k;

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

int	check_logical_symboles(char *line, int i, t_data *data, char *token)
{
	int	len;

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
			if (check_just_spaces((line + i + len), token) == 1 || line[i + len] == '\0')
			{
				data->error = 4;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	check_pipe(char *line, int i, t_data *data)
{
	if (line[i] == '|' && line[i + 1] != '|')
	{
		data->error = 1;
		return (0); 
	}
	while (line[i] != '\0')
	{
		if (line[i] == '|' && line[i + 1] != '|')
		{
			if (check_just_spaces((line + i), "|") == 1 || line[i + 1] == '\0')
			{
				data->error = 2;
				return (0);
			}
		}
		i++;
	}
	return (1);
}

int	parse(char *line, t_data *data)
{
    int 	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (check_quotes(line, i, data) == 0)
		return (0);
	if (check_pipe(line, i, data) == 0)
		return (0);
	if (check_logical_symboles(line,i, data, "&&") == 0)
		return (0);
	if (check_logical_symboles(line,i, data, "||") == 0)
		return (0);
	return (1);
}
