/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 16:29:41 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/27 16:29:50 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_env_path(t_environment *tmp, char *str)
{
	char	*s;

	if (ft_strcmp("PATH", str) == 0)
	{
		s = tmp->value;
		tmp->value = ft_strdup("./");
		free(s);
		return (1);
	}
	return (0);
}

void	check_to_delete(char *str)
{
	t_environment	*tmp;
	t_environment	*prev;

	tmp = g_lobal_minishell.environment;
	prev = NULL;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, str) == 0)
		{
			if (check_env_path(tmp, str) == 1)
				return ;
			else if (prev == NULL)
				g_lobal_minishell.environment = tmp->next;
			else
				prev->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	unset_builtin(char **args)
{
	int	i;

	i = 1;
	while (args[i] != NULL)
	{
		check_to_delete(args[i]);
		i++;
	}
	re_create_env();
}
