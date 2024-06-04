/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 11:21:58 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/24 11:22:01 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	pwd_builtin(char *str)
{
	char			*pwd;
	t_environment	*env;

	(void)str;
	env = g_lobal_minishell.environment;
	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		while (env != NULL)
		{
			if (ft_strcmp("PWD", env->key) == 0)
			{
				pwd = ft_strdup(env->value);
				break ;
			}
			env = env->next;
		}
	}
	printf("%s\n", pwd);
	free(pwd);
}
