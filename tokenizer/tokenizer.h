/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 17:39:50 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/15 17:39:59 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef enum
{
	WORD,
	PIP,
    O_AND,
    O_OR,
	RED_IN,
    RED_OUT,
	APPEND,
	HERDOC,
	BLOCK,
	L_BLOCK,
	R_BLOCK
} token;

token	get_token(char *str);