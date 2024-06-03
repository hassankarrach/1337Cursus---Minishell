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

int	is_exist(char *key, char *value, int flag, int flag2)
{
	int				i;
	t_environment	*tmp;

	tmp = g_lobal_minishell.environment;
	i = 0;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, key) == 0)
		{
			if (flag == 1)
				tmp->value = ft_strjoin(tmp->value, value);
			else if (flag2 == 1)
			{
				tmp->value = ft_strdup(value);
				free(value);
				tmp->flag = 0;
			}
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	printf_varibles(int flag)
{
	t_environment	*tmp;

	tmp = g_lobal_minishell.environment;
	while (tmp != NULL)
	{
		if (tmp->flag == 1 && flag == 0)
		{
			tmp = tmp->next;
			continue ;
		}
		printf("%s=", tmp->key);
		if (tmp->value != NULL)
			printf("%s\n", tmp->value);
		tmp = tmp->next;
	}
	if (flag == 1)
		g_lobal_minishell.status = 0;
}

int	check_to_create(char *str, int *j, int *flag, char *c)
{
	int	i;

	i = *j;
	if (str[i] == '+' && str[i + 1] == '=')
	{
		(*flag) = 1;
		(*c) = '+';
	}
	else if ((ft_isalnum(str[i]) == 0 && str[0] != '_') \
	|| (ft_isdigit(str[0]) == 1))
	{
		custom_error("minishell-1.0: Not a valid identifier: ", str, 1);
		return (1);
	}
	(*j)++;
	return (0);
}

void	create_env_var(char **args, int *i, int flag, char c)
{
	int		flag2;
	int		j;
	char	*key;
	char	*value;

	flag2 = 0;
	j = *i;
	value = NULL;
	key = ft_strdup_key(args[j], c);
	add_garbage(&g_lobal_minishell.garbage_head2, new_garbage(key));
	if (args[j][ft_strlen(key)] == '=' || args[j][ft_strlen(key)] == '+')
		flag2 = 1;
	if (flag2 == 1)
		value = ft_strdup((*(args + j)) + ft_strlen(key) + 1) + flag;
	else
		value = ft_strdup("\0");
	if (is_exist(key, value, flag, flag2) == 0)
	{
		if (flag2 == 1)
			flag2 = 0;
		else
			flag2 = 1;
		add_back_env(new_env(key, value, flag2));
	}
	(*i)++;
}

void	export_builtin(char **args)
{
	int		i;
	int		j;
	int		flag;
	char	c;

	if (args[1] == NULL)
		printf_varibles(1);
	else
	{
		i = 1;
		while (args[i] != 0)
		{
			j = 0;
			if (check_validity(&flag, &c, args[i], j) == 1)
				return ;
			while (args[i][j] != '=' && args[i][j] != '\0')
			{
				if (check_to_create(args[i], &j, &flag, &c) == 1)
					return ;
			}
			create_env_var(args, &i, flag, c);
		}
		re_create_env();
		g_lobal_minishell.status = 0;
	}
}
