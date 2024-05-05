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
	close(flag);
	if (ft_open_red(file_name, flag) == -1)
	{
		recover_stdio();
		if (access(file_name, F_OK) == 0)
			custom_error("minishell-1.0: Permission denied: ", file_name, 1);
		else
			custom_error("minishell-1.0: \
			No such file or directory: ", file_name, 1);
		return (1);
	}
	return (0);
}

int	out_redirection(char *file_name, int flag)
{
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
	close(1);
	if (ft_open_red(file_name, flag) == -1)
	{
		recover_stdio();
		if (access(file_name, F_OK) == 0)
			custom_error("minishell-1.0: Permission denied: ", file_name, 1);
		else
			custom_error("minishell-1.0: \
			No such file or directory: ", file_name, 1);
		return (1);
	}
	return (0);
}

void	heredoc_redirection(t_redir *redir, char *tmp, int flag, int *fd)
{
	char	*heredoc;

	while (1)
	{
		heredoc = readline("heredoc> ");
		if (heredoc == NULL)
			break ;
		if (flag == 1)
			check_to_expand(&heredoc);
		if (ft_strcmp(heredoc, redir->file_name) == 0)
			break ;
		ft_putstr_fd(heredoc, *fd, '\n');
	}
	close(*fd);
	if (redir->child != NULL && redir->child->type == TOKEN_WORD)
	{
		*fd = open(tmp, O_RDONLY, 0644);
		dup2(*fd, 0);
		close(*fd);
	}
}
