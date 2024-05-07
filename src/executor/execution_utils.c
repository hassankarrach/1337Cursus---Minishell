/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 06:12:24 by aelbasri          #+#    #+#             */
/*   Updated: 2024/04/07 06:13:31 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_and(t_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	if (g_lobal_minishell.status == 0)
		g_lobal_minishell.status = specify_types((t_tree *)and_or->right);
}

void	ft_or(t_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	if (g_lobal_minishell.status != 0)
		g_lobal_minishell.status = specify_types((t_tree *)and_or->right);
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
	int				j;
	char			*tmp1;
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
	j = 0;
	tmp = g_lobal_minishell.environment;
	while (tmp != NULL)
	{
		tmp1 = ft_strjoin(tmp->key, "=");
		env[j] = ft_strjoin(tmp1, tmp->value);
		tmp = tmp->next;
		j++;
	}
	env[j] = NULL;
	g_lobal_minishell.env = env;
}
