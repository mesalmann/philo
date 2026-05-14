NAME    = philo

CC      = cc
CFLAGS  = -Wall -Wextra -Werror -pthread

SRCS    = main.c \
          parse.c \
          init.c \
          clean.c \
          meal.c \
          philo.c \
          monitor.c \
          utils.c

OBJS    = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
