/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 21:21:53 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/22 21:21:56 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	check_directory(char *args)
{
	if (access(args, F_OK) != 0)
	{
		ft_putstr_fd("minishell-1.0: Not sush file or directory: ", 2, 4);
		ft_putstr_fd(args, 2, '\n');
	}
	else
	{
		ft_putstr_fd("minishell-1.0: Not a directory: ", 2, 4);
		ft_putstr_fd(args, 2, '\n');
	}
	g_lobal_minishell.status = 1;
}

void	ft_chdir(char *args)
{
	int				j;
	char			*oldpwd;

	oldpwd = getcwd(NULL, 0);
	j = chdir(args);
	if (j != 0)
		check_directory(args);
	else
	{
		g_lobal_minishell.status = 0;
		edit_environment("OLDPWD", oldpwd);
		edit_environment("PWD", getcwd(NULL, 0));
		re_create_env();
	}
}

void	custom_error(char *s1, char *s2, int status)
{
	ft_putstr_fd(s1, 2, 4);
	ft_putstr_fd(s2, 2, '\n');
	g_lobal_minishell.status = status;
}

void	cd_builtin(char **args)
{
	int				i;
	t_environment	*env;

	i = args_number(args);
	if (i > 2)
		custom_error("minishell-1.0: too many arguments: ", "cd", 1);
	else if (i == 1)
	{
		env = g_lobal_minishell.environment;
		while (env != NULL)
		{
			if (ft_strcmp("HOME", env->key) == 0)
			{
				ft_chdir(env->value);
				return ;
			}
			env = env->next;
		}
		custom_error("minishell-1.0: HOME not set: ", "cd", 1);
	}
	else
		ft_chdir(args[1]);
}
