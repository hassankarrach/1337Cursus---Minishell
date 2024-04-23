/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 08:39:42 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/23 08:39:46 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
/*
export and unset change envirenment and env(the therd argument i execv)
*/
int		builtins(char **args)
{
	if (ft_strcmp(args[0], "echo") == 0)
		return(echo_builtin(args));
	// else if (ft_strcmp(args[0], "cd") == 0)
	// 	return(cd_builtin(args));
	// else if (ft_strcmp(args[0], "pwd") == 0)
	// 	return(pwd_builtin(args));
	// else if (ft_strcmp(args[0], "export") == 0)
	// 	return(export_builtin(args));
	// else if (ft_strcmp(args[0], "unset") == 0)
	// 	return(unset_builtin(args));
	// else if (ft_strcmp(args[0], "env") == 0)
	// 	return(env_builtin(args));
	// else if (ft_strcmp(args[0], "exit") == 0)
	// 	return(exit_builtin(args));
	return(0);
}
