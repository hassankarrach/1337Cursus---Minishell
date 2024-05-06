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

int	count(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

char	**join_arg(char **args, char *value)
{
	char	**args1;
	int		len;
	int		i;

	len = 0;
	if (args != 0)
		len = count(args);
	args1 = (char **)malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (i < len)
	{
		args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(args[i]) + 1));
		args1[i] = ft_strdup(args[i]);
		i++;
	}
	args1[i] = (char *)malloc(sizeof(char) * (ft_strlen(value) + 1));
	args1[i] = ft_strdup(value);
	args1[++i] = NULL;
	return (args1);
}

t_cmd	*_cmd(char **args, int type, int i)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	new->args = args;
	new->type = type;
	new->args_number = i;
	return (new);
}

int	redir_node(char	***args, t_redir **hold, t_token **head, t_redir **redir)
{
	t_redir	*tmp1;
	char	**tmp;

	tmp = *args;
	if ((*head)->type == TOKEN_APPEND_REDIRECTION \
	|| (*head)->type == TOKEN_INPUT_REDIRECTION \
	|| (*head)->type == TOKEN_OUTPUT_REDIRECTION \
	|| (*head)->type == TOKEN_HEREDOC)
	{
		tmp1 = new_redir(head, (*head)->type);
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
	ft_free(tmp);
	return (0);
}

int	grass(t_token **head, t_tree **root, t_tree	*tmp, int flag)
{
	if ((*head)->type == TOKEN_WORD \
	|| (*head)->type == TOKEN_APPEND_REDIRECTION \
	|| (*head)->type == TOKEN_INPUT_REDIRECTION \
	|| (*head)->type == TOKEN_OUTPUT_REDIRECTION \
	|| (*head)->type == TOKEN_HEREDOC)
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
