/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelbasri <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 18:03:34 by aelbasri          #+#    #+#             */
/*   Updated: 2024/03/08 18:03:38 by aelbasri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "./utils/libft/libft.h"
# include "tokenizer/tokenizer.h"

# define GREEN "\033[1;32m"
# define RED "\033[1;31m"

typedef struct  s_data
{
    int		error;
    int     pipes_nbr;
    char    **my_env;
	t_environment	*envirnment;
} t_data;

// typedef struct s_tree
// {
//     int type;
//     struct s_tree *left;
//     struct s_tree *right;
// } t_tree;

typedef struct s_environment
{
    char	*key;
	char	*value;
    struct s_environment	*next;
} t_environment;

int	parse(char *line, t_data *data);
int	check_just_spaces(char *line, char *limiter) ;

#endif