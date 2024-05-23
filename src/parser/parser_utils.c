/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 17:05:04 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/04 17:05:06 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	heredoc_utils(char *tmp2, int *fd, t_redir *tmp1)
{
	tmp1->hc_sep = tmp2;
	*fd = open(tmp2, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	g_lobal_minishell.flag2 = 1;
	g_lobal_minishell.flag0 = check_quote_existence(tmp1->file_name);
	check_to_expand(&tmp1->file_name);
	g_lobal_minishell.flag2 = 0;
}

void	init_data(t_data *data)
{
	data->args = NULL;
	data->redir = NULL;
	data->hold = NULL;
	data->cmd = NULL;
}

t_cmd	*_cmd(char **args, int type, int i)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	add_garbage(&g_lobal_minishell.garbage_head, new_garbage(new));
	new->args = args;
	new->type = type;
	new->args_number = i;
	return (new);
}

int	is_redir(int type)
{
	if (type == TOKEN_APPEND_REDIRECTION \
	|| type == TOKEN_INPUT_REDIRECTION \
	|| type == TOKEN_OUTPUT_REDIRECTION \
	|| type == TOKEN_HEREDOC)
		return (1);
	return (0);
}

int	check_just_spaces(int flag, char **line, char *limiter)
{
	int	i;

	i = 0;
	(void)limiter;
	if (line == 0 || *line == 0)
		return (1);
	while ((*line)[i] != 0)
	{
		if ((*line)[i] != ' ' && (*line)[i] != '\t' && (*line)[i] != '\n')
		{
			if (flag == 1)
			{
				*line = ft_strdup((*line) + i);
				add_garbage(&g_lobal_minishell.garbage_head, \
				new_garbage(g_lobal_minishell.line));
			}
			return (0);
		}
		i++;
	}
	return (1);
}
