/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:05:04 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/04 17:05:06 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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