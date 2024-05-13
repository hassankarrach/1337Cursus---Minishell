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

void	io_redirections(t_redir *redir)
{
	if (redir->type == TOKEN_INPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (in_redirection(redir->file_name, 0) == 1)
			return ;
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_OUTPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (out_redirection(redir->file_name, 1) == 1)
			return ;
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_APPEND_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (out_redirection(redir->file_name, 2) == 1)
			return ;
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	return ;
}

int	check_quote_existence(char *file_name)
{
	int	i;

	i = 0;
	while (file_name[i] != '\0')
	{
		if (file_name[i] == '\'' || file_name[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

void	check_herdoc_to_expand(char **file_name, int *flag)
{
	char	*tmp;

	tmp = *file_name;
	recover_stdio();
	if (*file_name != NULL && check_quote_existence(*file_name) == 0)
		*flag = 1;
	else if ((*file_name)[0] == '\"')
	{
		*file_name = ft_strtrim(*file_name, "\"");
		free(tmp);
	}
	else if ((*file_name)[0] == '\'')
	{
		*file_name = ft_strtrim(*file_name, "\'");
		free(tmp);
	}
}

void	re_heredoc(t_redir *redir)
{
	int			old_fd;
	int			fd;
	int			flag;

	flag = 0;
	old_fd = dup(1);
	check_herdoc_to_expand(&redir->file_name, &flag);
	fd = open(redir->hc_sep, O_RDONLY, 0644);
	heredoc_redirection(redir, flag, &fd);
	dup2(old_fd, 1);
	close(old_fd);
	specify_types((t_tree *)redir->child);
}

void	exec_redir(t_tree *node)
{
	t_redir		*redir;

	redir = (t_redir *)node;
	g_lobal_minishell.status = 0;
	if (redir->type == TOKEN_INPUT_REDIRECTION || \
		redir->type == TOKEN_OUTPUT_REDIRECTION || \
		redir->type == TOKEN_APPEND_REDIRECTION)
		io_redirections(redir);
	else if (redir->type == TOKEN_HEREDOC)
		re_heredoc(redir);
}
