NAME = minishell

# Flags
CFLAGS = #-Wall -Wextra -Werror
RDLFLAG  = -lreadline

# Libs-Srcs
LIBFT = $(addprefix ./src/utils/libft/, ft_strlcpy.c ft_strrchr.c ft_strtrim.c ft_bzero.c ft_calloc.c ft_is_space.c ft_putstr_fd.c ft_split.c ft_strchr.c ft_strdup.c ft_strjoin.c ft_strlen.c ft_strncmp.c ft_substr.c)

# MiniShell-Srcs
SRC_TOKENIZER = $(addprefix ./src/tokenizer/, handle_tokens.c tokenizer_list.c tokenizer_utils.c tokenizer.c)
SRC_PARSER = $(addprefix ./src/parser/, parser.c)
SRC_EXPANDER = $(addprefix ./src/expander/, expand_wildcard.c)
SRCS = $(SRC_TOKENIZER) $(SRC_PARSER) $(SRC_EXPANDER) $(LIBFT) ./src/main.c

# Objects
OBJS = $(SRCS:.c=.o)

# Deps
all : $(NAME)

# Compiling
.c.o : 
	cc -g $(CFLAGS) -c -o $@ $^
$(NAME) : $(OBJS)
	cc -g $(CFLAGS) $(RDLFLAG) $(OBJS) -o $(NAME) 

# Cleaning
clean : 
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all 
