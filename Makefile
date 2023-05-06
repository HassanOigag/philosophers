CC = cc
CFLAGS =  -Wall -Werror -Wextra -fsanitize=thread
NAME = philo
SRCS = main.c utils.c init.c routine.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: clean fclean re all