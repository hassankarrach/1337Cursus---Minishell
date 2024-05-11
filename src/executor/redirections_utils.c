/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:46:52 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/05 12:46:55 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	recover_stdio(void)
{
	dup2(g_lobal_minishell.old_stdin, 0);
	dup2(g_lobal_minishell.old_stdout, 1);
}

int	ft_open_red(char *file_name, int flag)
{
	int	fd;

	fd = 0;
	if (flag == 0)
		fd = open(file_name, O_CREAT | O_RDONLY, 0644);
	else if (flag == 1)
		fd = open(file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else if (flag == 2)
		fd = open(file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
	return (fd);
}

int	in_redirection(char *file_name, int flag)
{
	int	fd;

	if (file_name == NULL)
	{
		recover_stdio();
		custom_error("minishell-1.0: ambiguous redirect", " ", 1);
		return (1);
	}
	if (access(file_name, F_OK) != 0)
	{
		recover_stdio();
		custom_error("minishell-1.0: \
No such file or directory: ", file_name, 1);
		return (1);
	}
	fd = ft_open_red(file_name, flag);
	if (fd == -1)
	{
		fd_error(file_name);
		return (1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}

int	out_redirection(char *file_name, int flag)
{
	int	fd;

	if (file_name == NULL)
	{
		recover_stdio();
		custom_error("minishell-1.0: ambiguous redirect", " ", 1);
		return (1);
	}
	if (ft_strcmp(file_name, "\0") == 0)
	{
		recover_stdio();
		custom_error("minishell-1.0: \
		No such file or directory: ", file_name, 1);
		return (1);
	}
	fd = ft_open_red(file_name, flag);
	if (fd == -1)
	{
		fd_error(file_name);
		return (1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

void	heredoc_redirection(t_redir *redir, char *tmp, int flag, int *fd)
{
	char	*heredoc;

	g_lobal_minishell.flag2 = 1;
	check_to_expand(&redir->file_name);
	g_lobal_minishell.flag2 = 0;
	while (1)
	{
		signal(SIGINT, &my_handler3);
		heredoc = readline("heredoc> ");
		if (heredoc == NULL)
			break ;
		if (ft_strcmp(heredoc, redir->file_name) == 0)
			break ;
		if (flag == 1)
			check_to_expand(&heredoc);
		ft_putstr_fd(heredoc, *fd, '\n');
	}
	recover_stdio();
	setup_signals();
	close(*fd);
	*fd = open(tmp, O_RDONLY, 0644);
	dup2(*fd, 0);
	close(*fd);
}
