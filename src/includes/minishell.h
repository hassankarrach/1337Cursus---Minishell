#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../utils/libft/libft.h"

// inner includes ===>
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
	int				*quote;
	int				a_counter;
	int				pipes_nbr;
	char			**my_env;
	int				status;
	pid_t			main_pid;
	char			**env;
	t_environment	*environment;
	t_token			*tokens;
    char			*line;
	t_tree			*root;
} t_minishell;

extern t_minishell global_minishell;


#endif