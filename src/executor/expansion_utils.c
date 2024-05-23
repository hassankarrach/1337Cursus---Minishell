/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:11:55 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/06 11:11:57 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	expand(char **str)
{
	t_environment	*tmp;

	if (*str == NULL)
		return ;
	(*str) = ft_strdup(((*str) + 1));
	tmp = g_lobal_minishell.environment;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->key, *str) == 0)
		{
			free(*str);
			(*str) = ft_strdup(tmp->value);
			add_garbage(&g_lobal_minishell.garbage_head, new_garbage(*str));
			return ;
		}
		tmp = tmp->next;
	}
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(*str));
	(*str) = ft_strdup(NULL);
}

void	cp_expanded(char **tmp, char **tmp1)
{
	char	*tmp2;
	int		i;
	char	*s;

	s = ft_itoa(g_lobal_minishell.status);
	if (ft_strncmp(tmp1[1], "$?", 2) == 0)
	{
		tmp1[1] = ft_strjoin(s, (tmp1[1]) + 2);
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp1[1]));
	}
	else if (ft_strcmp(tmp1[1], "$") != 0)
		expand(&(tmp1[1]));
	free(s);
	i = 0;
	tmp2 = ft_strjoin(tmp1[0], tmp1[1]);
	*tmp = ft_strjoin(tmp2, tmp1[2]);
}

void	_expand(char **tmp, int i)
{
	char	**tmp1;
	int		j;

	tmp1 = (char **)malloc(sizeof(char *) * 4);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp1));
	if (tmp1 == NULL)
		return ;
	i = 0;
	while (i < 4)
		tmp1[i++] = NULL;
	i = 0;
	while (*tmp && (*tmp)[i] != '\0')
	{
		if ((*tmp)[i] == '$')
		{
			j = ft_sublen((*tmp + i), ' ');
			tmp1[1] = ft_substr(*tmp, i, j);
			add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp1[1]));
			tmp1[2] = ft_substr(*tmp, (i + j), ft_strlen(*tmp + j));
			add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp1[2]));
		}
		i++;
	}
	if (tmp1[1] != NULL)
		cp_expanded(tmp, tmp1);
}

void	add_the_word(t_data data, t_list **head, char *str, int end)
{
	int		i;
	char	*tmp;
	t_list	*node;

	i = 0;
	tmp = NULL;
	if (str[data.start] == '\"' || str[data.start] == '\'')
		data.start++;
	if (data.flag == 1 && data.start >= end)
	{
		node = ft_lstnew("");
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(node));
		ft_lstadd_back(head, node);
		return ;
	}
	if (data.start <= end)
		tmp = ft_substr(str, data.start, end - data.start);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp));
	if (g_lobal_minishell.flag2 == 0 && (data.flag == 0 || data.flag == 1))
		_expand(&tmp, 0);
	if (data.flag == 0 && ft_strcmp(tmp, "") == 0)
		tmp = NULL;
	node = ft_lstnew(tmp);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(node));
	ft_lstadd_back(head, node);
}

void	va_init(t_data *data, int *i, t_list **head, char *str)
{
	*i = 0;
	data->start = 0;
	*head = NULL;
	data->end = ft_strlen(str);
}
