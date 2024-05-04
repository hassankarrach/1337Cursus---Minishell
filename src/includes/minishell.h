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
# include <errno.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../utils/libft/libft.h"

// inner includes ===>
# include "./error.h"
# include "./tokenizer.h"
# include "./parser.h"
# include "./executor.h"
# include "./garbage_collector.h"

// colors         ===>
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"

typedef struct s_minishell
{	
	int				error;
	int				pipes_nbr;
	int				*quote;
	int				a_counter;
	char			**my_env;
	int				status;
	pid_t			main_pid;
	int				old_stdin;
	int				old_stdout;
	char			**env;
	t_environment	*environment;
	t_token			*tokens;
    char			*line;
	t_tree			*root;
} t_minishell;

extern t_minishell g_lobal_minishell;

void	init_minishell(char *input);

#endif