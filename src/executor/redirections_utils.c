/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:46:52 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/24 15:59:58 by hkarrach         ###   ########.fr       */
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

void	heredoc_redirection(t_redir *redir, int flag, int *fd)
{
	char	*heredoc;
	char	*h;
	int		fd1;

	fd1 = open("/tmp/.heredocbuffer", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		heredoc = get_next_line(*fd);
		h = heredoc;
		if (heredoc == NULL)
			break ;
		if (flag == 1)
			check_to_expand(&heredoc);
		ft_putstr_fd(heredoc, fd1, 4);
		free(h);
	}
	recover_stdio();
	close(fd1);
	close(*fd);
	fd1 = open("/tmp/.heredocbuffer", O_RDONLY, 0644);
	dup2(fd1, 0);
	close(fd1);
	unlink(redir->hc_sep);
}
