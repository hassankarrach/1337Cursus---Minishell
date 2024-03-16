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

int	parse(char *line, t_data *data)
{
    int 	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')
		i++;
	if (check_quotes(line, i, data) == 0)
		return (0);
	return (1);
}
