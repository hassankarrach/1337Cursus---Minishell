/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 12:09:07 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/05 12:09:09 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	_redirections(t_redir *redir)
{
	if (redir->type == TOKEN_INPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (in_redirection(redir->file_name, 0) == 1)
			return (1);
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_OUTPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (out_redirection(redir->file_name, 1) == 1)
			return (1);
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_APPEND_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (out_redirection(redir->file_name, 2) == 1)
			return (1);
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	return (0);
}

void	check_herdoc_to_expand(char *file_name, int *flag)
{
	recover_stdio();
	if (file_name != NULL && (file_name)[0] != '\'' \
	&& (file_name)[0] != '\"' && (file_name)[0] != '$')
		*flag = 1;
}

void	exec_redir(t_tree *node)
{
	static int	h;
	t_redir		*redir;
	char		*tmp;
	int			flag;
	int			fd;

	redir = (t_redir *)node;
	flag = 0;
	g_lobal_minishell.status = 0;
	if (redir->type == TOKEN_INPUT_REDIRECTION || \
		redir->type == TOKEN_OUTPUT_REDIRECTION || \
		redir->type == TOKEN_APPEND_REDIRECTION)
	{
		if (_redirections(redir) == 1)
			return ;
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		check_herdoc_to_expand(redir->file_name, &flag);
		tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(h));
		fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		h++;
		heredoc_redirection(redir, tmp, flag, &fd);
		specify_types((t_tree *)redir->child);
	}
}
