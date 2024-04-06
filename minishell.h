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

typedef struct s_environment
{
	char	*key;
	char	*value;
	struct s_environment	*next;
} t_environment;

typedef struct s_line
{
	char	*component;
	struct s_line *next;
} t_line;

typedef struct s_data
{
	int				error;
	int				pipes_nbr;
	char			**my_env;
	t_environment	*environment;
	t_line			*line;
	t_tree			*root;
} t_data;

typedef struct s_tree
{
	int	type;
    struct s_tree	*left;
    struct s_tree	*right;
} t_tree;

typedef struct s_logical_operations
{
	int	type;
	struct s_logical_operations	*left;
    struct s_logical_operations	*right;
} l_op;

typedef struct s_block
{
	int	type;
	struct s_block	*left;
    struct s_block	*right;
} t_block;

typedef struct s_cmd
{
	int	type;
	union
	{
		char	*cmd;
		char	**args;
		int		in_f;
		int		out_f;
	};
	struct s_cmd	*left;
    struct s_cmd	*right;
} t_cmd;

typedef struct s_pip
{
	int	type;
	union
	{
		int		fd[2];
	};
	struct s_pip	*left;
    struct s_pip	*right;
} t_pip;


int	parse(char *line, t_data *data);
int	check_just_spaces(int flag, char **line, char *limiter) ;

#endif