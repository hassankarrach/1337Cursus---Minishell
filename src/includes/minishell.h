#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stddef.h>
# include <fcntl.h>
# include <stddef.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/wait.h>
# include "../utils/libft/libft.h"

// inner includes ===>
# include "./tokenizer.h"
# include "./executor.h"
# include "./garbage_collector.h"

// colors         ===>
# define GREEN "\033[1;32m"
# define RED "\033[1;31m"

typedef struct s_minishell
{	
	int				error;
	int				pipes_nbr;
	char			**my_env;
	int				status;
	pid_t			main_pid;
	char		**environment;
	// t_environment	*environment;
	t_token			*tokens;
    char			*line;
	t_tree			*root;
} t_minishell;

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
	char	**env;
	// char		**environment;
} t_cmd;

typedef struct s_pipe
{
	int	type;
	int	pipe_fd[2];
	struct s_pipe	*left;
    struct s_pipe	*right;
} t_pipe;

extern t_minishell global_minishell;


#endif