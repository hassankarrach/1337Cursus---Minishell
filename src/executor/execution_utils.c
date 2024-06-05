/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrac <hkarrac@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:12:24 by aelbasri          #+#    #+#             */
/*   Updated: 2024/06/05 10:06:10 by hkarrac          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_and(t_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	if (g_lobal_minishell.status == 0)
		specify_types((t_tree *)and_or->right);
}

void	ft_or(t_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	if (g_lobal_minishell.status != 0)
		specify_types((t_tree *)and_or->right);
}

void	wait_loop(void)
{
	int	j;

	j = 0;
	while (j++ < g_lobal_minishell.pipes_nbr)
		wait(NULL);
}

void	setup_in_out_fds(int p_fd1, int p_fd2, int std_fd)
{
	close(p_fd1);
	dup2(p_fd2, std_fd);
	close(p_fd2);
}

void	re_create_env(void)
{
	int				i;
	char			**env;
	t_environment	*tmp;

	tmp = g_lobal_minishell.environment;
	i = 0;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	env = (char **)malloc(sizeof(char *) * (i + 1));
	add_garbage(&g_lobal_minishell.garbage_head2, new_garbage(env));
	if (env == NULL)
	{
		g_lobal_minishell.flag1 = 0;
		return ;
	}
	copy_env(&env);
	g_lobal_minishell.env = env;
}
