/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 15:59:38 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/09 15:59:42 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	exec_block(t_tree *node)
{
	int		status = 0;
	t_block	*block;

	block = (t_block *)node;
	status = specify_types((t_tree *)block->child);
	return(status);
}

void	ft_and(l_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	g_lobal_minishell.status = status;
	if (g_lobal_minishell.status == 0)
		g_lobal_minishell.status = specify_types((t_tree *)and_or->right);
}
void	ft_or(l_op *and_or, int status)
{
	status = specify_types((t_tree *)and_or->left);
	g_lobal_minishell.status = status;
	if (g_lobal_minishell.status != 0)
		g_lobal_minishell.status = specify_types((t_tree *)and_or->right);
}

static int	exec_and_or(t_tree *node)
{
	int	status;
	int id;
	l_op *and_or;

	status = 0;
	and_or = (l_op *)node;
	if (and_or->type == TOKEN_AND)
		ft_and(and_or, status);
	else if (and_or->type == TOKEN_OR)
		ft_or(and_or, status);
	return (status);
}

static int	exec_pipe(t_tree *node)
{
	pid_t	id;
	int		i;
	t_pipe	*va_pipe;
	int		status;

	va_pipe = (t_pipe *)node;
	pipe(va_pipe->pipe_fd);
	id = fork();
	if (id == 0)
	{
		close(va_pipe->pipe_fd[0]);
		dup2(va_pipe->pipe_fd[1], 1);
		close(va_pipe->pipe_fd[1]);
		status = specify_types((t_tree *)(va_pipe->left));
		exit(g_lobal_minishell.status);
	}
	else
	{
		// printf("%d\n", va_pipe->index);
		// printf("%d\n", g_lobal_minishell.pipes_nbr);
		if (va_pipe->index == g_lobal_minishell.pipes_nbr)
			waitpid(id, &(g_lobal_minishell.status), 0);
		close(va_pipe->pipe_fd[1]);
		dup2(va_pipe->pipe_fd[0], 0);
		close(va_pipe->pipe_fd[0]);
		status = specify_types((t_tree *)(va_pipe->right));
		int j = 0;
		while (j++ < g_lobal_minishell.pipes_nbr)
				wait(NULL);
	}
	return(status);
}

static void	exec_cmd(t_tree *node)
{
	t_cmd	*cmd;
	int		flag;
	
	cmd = (t_cmd *)node;
	if ((g_lobal_minishell.root)->type != TOKEN_WORD)
		expansion(&(cmd->args), cmd->args_number);
	flag = check_builtins((cmd->args)[0]);
	if (flag >= 0 &&  flag <= 6)
		builtins(cmd->args, flag);
	else
		start_execution(cmd);
}

static void	exec_redir(t_tree *node)
{
	t_redir *redir;
	char	*heredoc;
	char	*tmp;
	int		flag;
	static int	h;
	int		fd;
	int		fd1;

	redir = (t_redir *)node;
	flag = 0;
	g_lobal_minishell.status = 0;
	if (redir->type == TOKEN_INPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (redir->file_name == NULL)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: ambiguous redirect ", 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		if (access(redir->file_name, F_OK) != 0)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		close(0);
		fd1 = open(redir->file_name, O_CREAT | O_RDONLY ,0644);
		if (fd1 == -1)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			if (access(redir->file_name, F_OK) == 0)
				ft_putstr_fd("minishell-1.0: Permission denied: ", 2, 4);
			else 
				ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_OUTPUT_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (redir->file_name == NULL)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: ambiguous redirect ", 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		if (ft_strcmp(redir->file_name, "\0") == 0)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		close(1);
		fd1 = open(redir->file_name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd1 == -1)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			if (access(redir->file_name, F_OK) == 0)
				ft_putstr_fd("minishell-1.0: Permission denied", 2, 4);
			else
				ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_APPEND_REDIRECTION)
	{
		check_to_expand(&(redir->file_name));
		if (redir->file_name == NULL)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: ambiguous redirect ", 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		if (ft_strcmp(redir->file_name, "\0") == 0)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		close(1);
		fd1 = open(redir->file_name, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd1 == -1)
		{
			dup2(g_lobal_minishell.old_stdin, 0);
			dup2(g_lobal_minishell.old_stdout, 1);
			if (access(redir->file_name, F_OK) == 0)
				ft_putstr_fd("minishell-1.0: Permission denied", 2, 4);
			else
				ft_putstr_fd("minishell-1.0: No such file or directory: ", 2, 4);
			ft_putstr_fd(redir->file_name, 2, '\n');
			g_lobal_minishell.status = 1;
			return ;
		}
		g_lobal_minishell.status = 0;
		specify_types((t_tree *)redir->child);
	}
	else if (redir->type == TOKEN_HEREDOC)
	{
		dup2(g_lobal_minishell.old_stdin, 0);
		dup2(g_lobal_minishell.old_stdout, 1);
		if (redir->file_name != NULL && (redir->file_name)[0] != '\'' && (redir->file_name)[0] != '\"' && (redir->file_name)[0] != '$')
			flag = 1;
		tmp = ft_strjoin("/tmp/.heredoc", ft_itoa(h));
		fd = open(tmp, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		h++;
		while(1)
		{
			heredoc = readline("heredoc> ");
			if (heredoc == NULL)
				break ;
			if(flag == 1)
				check_to_expand(&heredoc);
			if (ft_strcmp(heredoc ,redir->file_name) == 0)
				break ;
			ft_putstr_fd(heredoc, fd, '\n');
		}
		close(fd);
		if (redir->child != NULL && redir->child->type == TOKEN_WORD)
		{	
			fd = open(tmp, O_RDONLY, 0644);
			dup2(fd, 0);
			close(fd);
		}
		specify_types((t_tree *)redir->child);
	}
}

int	specify_types(t_tree *node)
{
	if (node == NULL)
	{
		dup2(g_lobal_minishell.old_stdin, 0);
		dup2(g_lobal_minishell.old_stdout, 1);
		return(0);
	}
	else if (node->type == TOKEN_WORD)
		exec_cmd(node);
	else if (node->type == TOKEN_PIPE)
		return (exec_pipe(node));
	else if (node->type == TOKEN_APPEND_REDIRECTION || node->type == TOKEN_INPUT_REDIRECTION\
	|| node->type == TOKEN_OUTPUT_REDIRECTION || node->type == TOKEN_HEREDOC)
		exec_redir(node);
	else if (node->type ==  TOKEN_AND || node->type == TOKEN_OR)
		return (exec_and_or(node));
	else if (node->type == TOKEN_BLOCK)
		return (exec_block(node));
	return (0);
}

void	execute()
{
	if (!(g_lobal_minishell.root))
		return ;
	specify_types(g_lobal_minishell.root);
}
