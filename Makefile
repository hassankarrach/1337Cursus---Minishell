NAME = minishell

# Flags
CFLAGS = -Wall -Wextra -Werror #-fsanitize=address
RDLFLAG = -lreadline

# Libs-Srcs
LIBFT = $(addprefix ./src/utils/libft/, ft_strlcpy.c ft_strrchr.c ft_strtrim.c ft_bzero.c ft_calloc.c ft_is_space.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_strcmp.c ft_substr.c ft_itoa.c ft_lstnew.c ft_lstadd_back.c ft_lstlast.c ft_lstsize.c ft_isalpha.c ft_isalnum.c ft_isdigit.c ft_atoi.c)
GNL = ./src/utils/get_next_line/get_next_line.c
# MiniShell-Srcs
SRC_MAIN = $(addprefix ./src/, main.c minishell.c)
SRC_EXPANDER = $(addprefix ./src/expander/, expand_wildcard.c)
SRC_G_COLLECTOR = $(addprefix ./src/garbage_collector/, garbage_collector.c)
SRC_TOKENIZER = $(addprefix ./src/tokenizer/, handle_tokens.c tokenizer_list.c tokenizer_utils.c tokenizer.c)
SRC_PARSER = $(addprefix ./src/parser/, build_tree.c parser_utils.c build_tree_utils.c linking.c node_creation.c syntax_check.c parser.c)
SRC_EXECUTOR = $(addprefix ./src/executor/, execute.c execution_utils.c environement.c exec.c redirections.c redirections_utils.c check_cmd.c expansion.c expansion_utils.c setup_signals.c)
SRC_BUILT_INS = $(addprefix ./src/executor/built_ins/, builtins.c echo_builtin.c cd_builtin.c pwd_builtin.c export_builtin.c unset_builtin.c env_builtin.c exit_builtin.c builtins_utils.c)
HEADERS = $(addprefix ./src/includes/, executor.h minishell.h parser.h tokenizer.h)

SRCS = $(SRC_TOKENIZER) $(SRC_EXECUTOR) $(SRC_BUILT_INS) $(LIBFT) $(GNL) $(SRC_PARSER) $(SRC_MAIN) $(SRC_G_COLLECTOR) $(SRC_EXPANDER)

# Objects
OBJS = $(SRCS:.c=.o)

# Deps
all: $(NAME)

# Compiling
.c.o:
	cc $(CFLAGS) -c -o $@ $<

$(NAME): $(OBJS) $(HEADERS)
	cc $(CFLAGS) $(OBJS) $(RDLFLAG) -o $(NAME)

# Cleaning
clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
