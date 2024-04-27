/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:28:19 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/27 17:28:21 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	exit_builtin(char **args)
{
	int	i;
	int	j;
	int	k;
	int	nbr;

	i = 1;
	j = 0;
	while (args[i][j] != '\0')
	{
		if (j == 0 && (args[i][j] == '-' || args[i][j] == '+'))
		{
			j++;
			continue ;
		}
		if (ft_isdigit(args[i][j]) == 0)
		{
			printf("exit\n");
			ft_putstr_fd("minishell-1.0: Numeric argument required: ", 2, 4);
			ft_putstr_fd(args[i], 2, '\n');
			global_minishell.status = 2;
			exit(global_minishell.status);
		}
		j++;
	}
	if (args[2] != NULL)
	{
		printf("exit\n");
		ft_putstr_fd("minishell-1.0: too many arguments: exit", 2, '\n');
		global_minishell.status = 1;
	}
	else
	{
		nbr = ft_atoi(args[i]);
		printf("exit\n");
		exit(nbr%256);
	}
}

