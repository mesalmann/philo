NAME    = philo

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pthread

SRCS    = main.c \
          parsing.c \
          arg_check.c \
          init.c \
          utils.c \
          synchro_utils.c \
          time_utils.c \
          dinner.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
