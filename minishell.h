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

# include <sys/types.h>
# include <sys/wait.h>
# include <stdio.h>
# include <fcntl.h>
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

typedef struct s_tree
{
	int	type;
} t_tree;

typedef struct s_data
{	
	int				error;
	int				pipes_nbr;
	char			**my_env;
	int				status;
	pid_t			main_pid;
	t_environment	*environment;
	t_line			*line;
	t_tree			*root;
} t_data;

typedef struct s_logical_operations
{
	int	type;
	struct s_logical_operations	*left;
    struct s_logical_operations	*right;
} l_op;

typedef struct s_redir
{
	int	type;
    char *file_name;
	struct s_redir	*child;
} t_redir;

typedef struct s_block
{
	int	type;
	struct s_block	*child;
} t_block;

typedef struct s_cmd
{
	int	type;
	char	**args;
	t_environment	*env;
} t_cmd;

typedef struct s_pipe
{
	int	type;
	int	pipe_fd[2];
	struct s_pipe	*left;
    struct s_pipe	*right;
} t_pipe;


int		parse(char *line, t_data *data);
int		check_just_spaces(int flag, char **line, char *limiter);
void	execute(t_data *data);
int		specify_types(t_tree *node);
void check_cmd(char **args, t_environment *env);

#endif