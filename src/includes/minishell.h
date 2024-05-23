/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkarrach <hkarrach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 15:46:27 by aelbasri          #+#    #+#             */
/*   Updated: 2024/05/23 13:50:13 by hkarrach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <unistd.h>
# include <signal.h>
# include <errno.h>
# include <sys/stat.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../utils/libft/libft.h"
# include "../utils/get_next_line/get_next_line.h"
# include "./error.h"
# include "./tokenizer.h"
# include "./parser.h"
# include "./executor.h"
# include "./garbage_collector.h"
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"

# define PROMPT "> minishell-1.0$ "

typedef struct s_minishell
{
	int				error;
	int				flag0;
	int				flag2;
	int				flag3;
	int				flag1;
	int				hc;
	int				pipes_nbr;
	int				*quote;
	int				a_counter;
	char			**my_env;
	int				status;
	int				sig;
	pid_t			main_pid;
	int				old_stdin;
	int				old_stdout;
	char			**env;
	t_environment	*environment;
	t_token			*tokens;
	t_garbage_node	*garbage_head;
	t_garbage_node	*garbage_head2;
	char			*line;
	t_tree			*root;
}	t_minishell;

extern t_minishell	g_lobal_minishell;

void	handle_expand_asterisk_wildcard(t_token **list, char *pattern);
char	**get_all_files_in_curr_dir(void);
int		is_containing_asterisk(char *str);

int		init_minishell(char *input);
int		check_input(char **input);
void	init(char ***env);
void	close_io(void);

#endif
