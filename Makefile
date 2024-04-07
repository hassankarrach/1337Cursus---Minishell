CFLAGS = #-Wall -Wextra -Werror
RDLFLAG  = -lreadline
SRCS = main.c executor/execution_utils.c executor/execute.c parser/parse.c utils/libft/ft_putstr_fd.c utils/libft/ft_split.c utils/libft/ft_strdup.c utils/libft/ft_strjoin.c utils/libft/ft_strlen.c utils/libft/ft_strncmp.c

HEADERS = minishell.h utils/libft/libft.h
NAME = minishell
OBJS = $(SRCS:.c=.o)

all : $(NAME)

.c.o : 
	cc $(CFLAGS) -c -o $@ $^
$(NAME) : $(OBJS) $(HEADERS)
	cc $(CFLAGS) $(RDLFLAG) $(OBJS) -o $(NAME) 
clean : 
	rm -f $(OBJS)
fclean : clean
	rm -f $(NAME)
re : fclean all 

.SECONDARY: $(OBJS)
.PHONY: all clean fclean re
