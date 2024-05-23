/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 17:10:57 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/27 17:10:59 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	env_builtin(char **args)
{
	if (args[1] != NULL)
	{
		ft_putstr_fd("minishell-1.0: too many arguments: env", 2, '\n');
		g_lobal_minishell.status = 1;
	}
	else
		printf_varibles(0);
}
