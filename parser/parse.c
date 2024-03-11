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

void	ft_exit(int id)
{
	if (id == 1)
	{
		ft_putstr_fd("\033[1;32mSyntax Error : unclosed pip\033[0m", 2);
	}
	if (id == 2)
	{
		ft_putstr_fd("\033[1;32mSyntax Error : unclosed quote\033[0m", 2);
			exit(1);
	}
}

void	check_pipes(char *line, t_data *data)
{
	char	**tmp;
	int		i;

	while(line[i] != 0)
	{
		if (line[i] == '')
	}
}

void	parse(char *line, t_data *data)
{
	if (!check_pipes(line, data))
		ft_exit(1);
	if (!check_quotes(line))
		ft_exit(2);
}