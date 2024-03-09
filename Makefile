CFLAGS = -Wall -Wextra -Werror
RDLFLAG  = -lreadline
SRCS = main.c parser/parse.c executor/execute.c

HEADERS = minishell.h
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
