/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 17:24:03 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/20 17:30:43 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_garbage_node	*new_garbage(void *garbage_ptr)
{
	t_garbage_node	*garbage;

	garbage = (t_garbage_node *)malloc(sizeof(t_garbage_node));
	if (!garbage)
		return (NULL);
	garbage->garbage_ptr = garbage_ptr;
	garbage->next = NULL;
	return (garbage);
}

void	add_garbage(t_garbage_node **lst, t_garbage_node *new_garbage)
{
	t_garbage_node	*curr_garbage;

	if (!(*lst))
	{
		(*lst) = new_garbage;
		return ;
	}
	curr_garbage = *lst;
	while (curr_garbage && curr_garbage -> next)
		curr_garbage = curr_garbage -> next;
	curr_garbage -> next = new_garbage;
}

static void	free_token_nodes(t_token **head)
{
	t_token	*_head;
	t_token	*_tmp;

	_head = *head;
	while (_head)
	{
		_tmp = _head;
		_head = _head->next;
		free (_tmp->value);
		free (_tmp);
	}
	*head = NULL;
}

void	add_double_ptr_garbages(char **double_ptr)
{
	int	i;

	i = 0;
	while (double_ptr[i])
	{
		add_garbage(&g_lobal_minishell.garbage_head,
			new_garbage(double_ptr[i]));
		i++;
	}
	add_garbage(&g_lobal_minishell.garbage_head,
		new_garbage(double_ptr));
}

void	clear_garbage(t_garbage_node **head)
{
	t_garbage_node	*curr_node;
	t_garbage_node	*next;

	curr_node = *head;
	free_token_nodes(&g_lobal_minishell.tokens);
	if (!curr_node)
		return ;
	while (curr_node)
	{
		next = curr_node->next;
		if (curr_node->garbage_ptr)
			free(curr_node->garbage_ptr);
		free(curr_node);
		curr_node = next;
	}
	*head = NULL;
}
