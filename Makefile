NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = actions.c\
	   free.c\
	   init.c\
	   monitor.c\
	   mutex_utils.c\
	   routine.c\
	   start_thread.c\
	   utils.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
