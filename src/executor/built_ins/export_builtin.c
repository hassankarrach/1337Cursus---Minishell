/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 12:23:19 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/24 12:23:21 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_strlen_end(char *str, char end)
{
	int i;

	i = 0;
	while (str[i] != 0 || str[i] != end)
		i++;
	return (i);
}

void	add_back_env(t_environment *new)
{
	t_environment	*tmp;

	tmp = global_minishell.environment;
	if (tmp != NULL)
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

int	is_exist(char *key, char *value, int flag, int flag2)
{
	int				i;
	t_environment	*tmp;
	tmp = global_minishell.environment;

	i = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (flag == 1)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (flag2 == 1)
				tmp->value = ft_strdup(value);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}
void	printf_varibles(int flag)
{
	t_environment	*tmp;

	tmp = global_minishell.environment;
	while(tmp != NULL)
	{
		if (tmp->flag == 1 && flag == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}

void	export_builtin(char **args)
{
	int		i;
	int		j;
	int		flag;
	int		flag2;
	char	*key;
	char	*value;
	char	c;

	if (args[1] == NULL)
		printf_varibles(1);
	else
	{
		i = 1;
		while (args[i] != 0)
		{
			j = 0;
			flag = 0;
			c = '=';
			if (args[i][j] == '=')
			{
				ft_putstr_fd("minishell-1.0: Not a valid identifier: ", 2, 4);
				ft_putstr_fd(args[i], 2, '\n');
				global_minishell.status = 1;
				return ;
			}
			while (args[i][j] != '=' &&  args[i][j] != '\0')
			{
				if (args[i][j] == '+' && args[i][j + 1] == '=')
				{
					flag = 1;
					c = '+';
				}
				else if ((ft_isalnum(args[i][j]) == 0 && args[i][0] != '_') || (ft_isdigit(args[i][0]) == 1))
				{
					ft_putstr_fd("minishell-1.0: Not a valid identifier: ", 2, 4);
					ft_putstr_fd(args[i], 2, '\n');
					global_minishell.status = 1;
					return ;
				}
				j++;
			}
			flag2 = 0;
			key = ft_strdup_key(args[i], c);
			if (args[i][ft_strlen(key)] == '=')
				flag2 = 1;
			value = ft_strdup((*(args + i)) + ft_strlen(key) + 1) + flag;
			if (is_exist(key, value, flag, flag2) == 0)
				add_back_env(new_env(key, value, 1));
			i++;
		}
		re_create_env();
	}
}