/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:09:02 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/23 08:09:06 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_n_option(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	check_options(char **args)
{
	int	i;

	i = 1;
	while(args[i] != NULL)
	{
		if (check_n_option(args[i]) == 0)
			return (i);
		i++;
	}
	return (i);
}

void ft_print(char **str, int index)
{
	char	c;
	char	c1;

	if (index == 1)
		c = '\n';
	else
		c = 4;
	c1 = ' ';
	while (str[index] != NULL)
	{
		if (str[index + 1] == NULL)
			c1 = 4;
		printf("%s%c", str[index++], c1);
	}
	printf("%c",c);

}
// if index != 0 print without \n 
int	echo_builtin(char **args)
{
	int	index;

	index = check_options(args);
	ft_print(args, index);
	return (1);
}
