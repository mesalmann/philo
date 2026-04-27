NAME    = philo

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror -pthread

SRCS    = main.c \
          parsing.c \
          arg_check.c \
          init.c \
          utils.c \
          time_utils.c \
          routine.c \
          clean.c \
          monitor.c \
          actions.c \
          print.c \
          state.c \
          lifecycle.c

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
