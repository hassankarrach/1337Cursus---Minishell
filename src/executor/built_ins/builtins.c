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
export, cd, unset change envirenment and env(the therd argument i execv)
*/

int	args_number(char **args)
{
	int	i;

	i = 0;
	while(args[i] != 0)
		i++;
	return (i);
}

void	edit_environment(char *str, char *new)
{
	t_environment	*env;

	env = global_minishell.environment;
	while (env != NULL)
	{
		if(ft_strcmp(env->key, str) == 0)
		{
			free(env->value);
			env->value = new;
			return ;
		}
		env = env->next;
	}
}

int	check_builtins(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (0);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (2);
	else if (ft_strcmp(cmd, "export") == 0)
		return (3);
	else if (ft_strcmp(cmd, "unset") == 0)
		return(4);
	else if (ft_strcmp(cmd, "env") == 0)
		return(5);
	else if (ft_strcmp(cmd, "exit") == 0)
		return(6);
	return (-1);
}

void	builtins(char **args, int flag)
{
	if (flag == 0)
		echo_builtin(args);
	else if (flag == 1)
		cd_builtin(args);
	else if (flag == 2)
		pwd_builtin(args);
	else if (flag == 3)
		export_builtin(args);
	else if (flag == 4)
		unset_builtin(args);
	else if (flag == 5)
		return(env_builtin(args));
	else if (flag == 6)
		return(exit_builtin(args));
}
