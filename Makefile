NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -I include

SRCS = src/actions.c\
	   src/forks.c\
	   src/init.c\
	   src/main.c\
	   src/monitor.c\
	   src/mutex_utils.c\
	   src/routine.c\
	   src/start_thread.c\
	   src/time.c\
	   src/utils.c

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
