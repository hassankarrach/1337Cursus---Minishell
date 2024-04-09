NAME = minishell

# Flags
CFLAGS = #-Wall -Wextra -Werror
RDLFLAG  = -lreadline

# Libs-Srcs
LIBFT = $(addprefix ./src/utils/libft/, ft_bzero.c ft_calloc.c ft_is_space.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c)

# MiniShell-Srcs
SRC_TOKENIZER = $(addprefix ./src/tokenizer/, handle_tokens.c tokenizer_list.c tokenizer_utils.c tokenizer.c)
SRC_EXECUTOR = $(addprefix ./src/executor/, execute.c execution_utils.c)
SRCS = $(SRC_TOKENIZER) $(SRC_EXECUTOR) $(LIBFT) ./src/main.c

# Objects
OBJS = $(SRCS:.c=.o)

# Deps
all : $(NAME)

# Compiling
.c.o : 
	cc $(CFLAGS) -c -o $@ $^
$(NAME) : $(OBJS)
	cc $(CFLAGS) $(RDLFLAG) $(OBJS) -o $(NAME) 

# Cleaning
clean : 
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all 
