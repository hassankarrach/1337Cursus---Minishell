/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_tree_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:12:35 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/06 15:12:38 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**join_arg(char **args, char *value)
{
	char	**args1;
	int		len;
	int		i;

	len = 0;
	if (args != 0)
		len = count(args);
	args1 = (char **)malloc(sizeof(char *) * (len + 2));
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(args1));
	i = 0;
	while (i < len)
	{
		args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(args1[i]));
		args1[i] = ft_strdup(args[i]);
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(args1[i]));
		i++;
	}
	args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(args1[i]));
	args1[i] = ft_strdup(value);
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(args1[i]));
	args1[++i] = NULL;
	return (args1);
}

void	restor_sigdfl(int fd)
{
	signal(SIGINT, &my_handler);
	dup2(g_lobal_minishell.old_stdin, 0);
	close(fd);
}

void	open_heredoc(t_redir *tmp1, int	*h)
{
	char		*tmp2;
	int			fd;
	char		*tmp;
	char		*heredoc;

	if (tmp1->type == TOKEN_HEREDOC)
	{
		(*h)++;
		signal(SIGINT, &my_handler3);
		tmp = ft_itoa(*h);
		tmp2 = ft_strjoin("/tmp/.heredoc", tmp);
		free(tmp);
		add_garbage(&g_lobal_minishell.garbage_head, new_garbage(tmp2));
		heredoc_utils(tmp2, &fd, tmp1);
		while (1)
		{
			heredoc = readline("heredoc> ");
			if (heredoc == NULL)
				break ;
			if (ft_strcmp(heredoc, tmp1->file_name) == 0)
				break ;
			ft_putstr_fd(heredoc, fd, '\n');
		}
		restor_sigdfl(fd);
	}
}

int	redir_node(char	***args, t_redir **hold, t_token **head, t_redir **redir)
{
	char		**tmp;
	t_redir		*tmp1;
	static int	h;

	tmp = *args;
	if (is_redir((*head)->type) == 1)
	{
		tmp1 = new_redir(head, (*head)->type);
		open_heredoc(tmp1, &h);
		if (g_lobal_minishell.hc == 1)
			return (0);
		if ((*redir) != NULL)
		{
			(*redir)->child = (t_tree *)tmp1;
			(*redir) = (t_redir *)(*redir)->child;
		}
		else
		{
			(*redir) = tmp1;
			(*hold) = (*redir);
		}
		return (1);
	}
	*args = join_arg(tmp, (*head)->value);
	return (0);
}

int	grass(t_token **head, t_tree **root, t_tree	*tmp, int flag)
{
	if ((*head)->type == TOKEN_WORD || is_redir((*head)->type) == 1)
	{
		new_cmd(head, root);
		return (1);
	}
	else if ((*head)->type == TOKEN_PIPE)
		new_pipe(root);
	else if ((*head)->type == TOKEN_AND || (*head)->type == TOKEN_OR)
		new_op(root, (*head)->type);
	else if ((*head)->type == TOKEN_OPENING_PARENTHESES)
	{
		tmp = build_tree((*head)->next, 2);
		new_block(root, tmp, head);
	}
	else if ((*head)->type == TOKEN_CLOSING_PARENTHESES)
	{
		if (flag == 2)
			return (2);
	}
	return (0);
}
