/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 11:11:41 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/06 11:11:45 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	check_to_expand2(int i, char *str, t_list **head, t_data *data)
{
	if ((str)[i] == '\'' && data->flag == 0)
	{
		data->end = i;
		add_the_word(*data, head, str, data->end);
		data->flag = 2;
	}
	else if ((str)[i] == '\'' && data->flag == 2)
	{
		data->end = i;
		add_the_word(*data, head, str, data->end);
		data->flag = 0;
	}
	else if ((str)[i] == '\"' && data->flag == 0)
	{
		data->end = i;
		add_the_word(*data, head, str, data->end);
		data->flag = 1;
	}
	else if ((str)[i] == '\"' && data->flag == 1)
	{
		data->end = i;
		add_the_word(*data, head, str, data->end);
		data->flag = 0;
	}
	data->start = data->end;
}

void	re_create_str(char **str, t_list *head)
{
	char	*tmp1;

	tmp1 = NULL;
	while (head != NULL)
	{
		*str = ft_strjoin(tmp1, (char *)(head->content));
		tmp1 = *str;
		head = head->next;
	}
}

void	check_to_expand(char **str)
{
	int		i;
	t_list	*head;
	t_data	data;
	char	*tmp;

	data.flag = 0;
	tmp = (*str);
	va_init(&data, &i, &head, *str);
	while ((*str)[i] != '\0')
	{

		if ((*str)[i] == '\'' || (*str)[i] == '\"')
			check_to_expand2(i, *str, &head, &data);
		else if ((*str)[i] == '$' && data.flag != 2)
			add_the_word(data, &head, *str, i);
		i++;
	}
	if (data.start != i)
		add_the_word(data, &head, *str, i);
	re_create_str(str, head);
}

void	edit_args(char ***args, int nb)
{
	int		i;
	int		j;
	char	**tmp;
	char	**new_args;

	i = 0;
	j = 0;
	new_args = (char **)malloc(sizeof(char *) * (nb + 1));
	tmp = *args;
	while (i < nb)
	{
		if (tmp[i] != NULL)
		{
			new_args[j] = ft_strdup(tmp[i]);
			j++;
		}
		i++;
	}
	while (j < nb + 1)
		new_args[j++] = NULL;
	*args = new_args;
}

void	expansion(char ***args, int nb)
{
	char	**tmp;
	int		i;

	tmp = *args;
	i = 0;
	while (tmp != NULL && tmp[i] != NULL)
	{
		// printf("1(%s)\n", tmp[i]);
		check_to_expand(&(tmp[i]));
		// printf("2(%s)\n", tmp[i]);
		i++;
	}
	edit_args(args, nb);
}
