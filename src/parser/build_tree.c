/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 22:18:33 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/23 15:56:43 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_tree	*build_tree(t_token *head, int flag)
{
	t_tree	*root;
	t_tree	*tmp;
	int		i;

	root = NULL;
	tmp = NULL;
	while (head)
	{
		i = grass(&head, &root, tmp, flag);
		if (g_lobal_minishell.hc == 1)
			return (NULL);
		if (i == 1)
			continue ;
		else if (i == 2)
			return (root);
		head = head->next;
	}
	return (root);
}
