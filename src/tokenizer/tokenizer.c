/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 16:51:25 by hkarrach          #+#    #+#             */
/*   Updated: 2024/05/25 11:18:19 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*tokens_list;

	line = g_lobal_minishell.line;
	tokens_list = handle_tokens(line);
	return (tokens_list);
}
