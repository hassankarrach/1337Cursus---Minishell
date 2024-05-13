/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environement.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:06:53 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/04 17:06:58 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	ft_sublen(const char *s, char c)
{
	size_t	i;

	i = 0;
	if (c == ' ')
	{
		while (s[i] != '\0' && ft_is_space(s[i]) != 1 && s[i] != '\'')
		{
			i++;
			if (s[i] == '$')
				break ;
		}
	}
	else
	{
		while (s[i] != '\0' && s[i] != c)
			i++;
	}
	return (i);
}

char	*ft_strdup_key(const char *s, char c)
{
	int		i;
	char	*str;
	int		j;

	i = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
		i++;
	str = (char *)malloc(sizeof(char) * (i + 1));
	if (!str)
		return (NULL);
	j = 0;
	while (j < i && s[j] != 0)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

t_environment	*new_env(char *key, char *value, int flag)
{
	t_environment	*v_env;

	v_env = malloc(sizeof(t_environment));
	if (!v_env)
		return (NULL);
	v_env->key = key;
	v_env->value = value;
	v_env->flag = flag;
	v_env->next = NULL;
	return (v_env);
}

void	setup_environment(char **env ,int flag)
{
	int				i;
	int				key_len;
	char			*h_key;
	char			*h_value;
	t_environment	*tmp;

	(void)flag;
	if (g_lobal_minishell.env != NULL && env != NULL && (*env) == NULL)
		return ;
	h_key = ft_strdup_key((g_lobal_minishell.env)[0], '=');
	h_value = ft_strdup(*(g_lobal_minishell.env) + (ft_strlen(h_key) + 1));
	g_lobal_minishell.environment = new_env(h_key, h_value, 0);
	tmp = g_lobal_minishell.environment;
	i = 1;
	while ((g_lobal_minishell.env)[i] != NULL)
	{
		// free(h_key);
		h_key = ft_strdup_key(g_lobal_minishell.env[i], '=');
		key_len = ft_strlen(h_key) + 1;
		// free(h_value);
		h_value = ft_strdup(*(g_lobal_minishell.env + i) + key_len);
		tmp->next = new_env(h_key, h_value, 0);
		tmp = tmp->next;
		i++;
	}
}
