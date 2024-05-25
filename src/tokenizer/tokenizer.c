/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:51:25 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/25 09:28:23 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token_type get_last_token(t_token **head)
{
	t_token *tmp = *head;
	t_token *curr = *head;
	t_token_type res;

	while (curr)
	{
		if (curr->type != TOKEN_WHITE_SPACE)
			res = curr->type;
		curr = curr->next;
	}
	*head = tmp;
	return (res);
}

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*tokens_list;

	line = g_lobal_minishell.line;
	tokens_list = handle_tokens(line);
	return (tokens_list);
}
