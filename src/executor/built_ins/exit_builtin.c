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

void	b_exit(char *str)
{
	int	nbr;

	if (str == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	nbr = ft_atoi(str);
	printf("exit\n");
	exit(nbr % 256);
}

void	check_is_digit(char *str, int *j)
{
	if (ft_isdigit(str[*j]) == 0)
	{
		printf("exit\n");
		custom_error("minishell-1.0: Numeric argument required: ", str, 2);
		exit(g_lobal_minishell.status);
	}
	(*j)++;
}

void	exit_builtin(char **args)
{
	int	i;
	int	j;
	int	k;

	i = 1;
	j = 0;
	while (args[i] != NULL && args[i][j] != '\0')
	{
		if (j == 0 && (args[i][j] == '-' || args[i][j] == '+'))
		{
			j++;
			continue ;
		}
		check_is_digit(args[i], &j);
	}
	if (args[2] != NULL)
	{
		printf("exit\n");
		custom_error("minishell-1.0: too many arguments: ", "exit", 1);
	}
	else
		b_exit(args[i]);
}
