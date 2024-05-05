/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 09:54:49 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/05 09:54:52 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_end(char *str, char end)
{
	int	i;

	i = 0;
	while (str[i] != 0 || str[i] != end)
		i++;
	return (i);
}

void	add_back_env(t_environment *new)
{
	t_environment	*tmp;

	tmp = g_lobal_minishell.environment;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	check_validity(int *flag, char *c, char *str, int j)
{
	(*flag) = 0;
	(*c) = '=';
	if (str[j] == '=')
		custom_error("minishell-1.0: Not a valid identifier: ", str, 1);
}
