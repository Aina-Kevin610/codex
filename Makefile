NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = srcs/codexion.c \
	srcs/parsing.c \
	srcs/coder.c \
	srcs/utils.c \
	srcs/action.c \
	srcs/process.c \
	srcs/request.c \
	srcs/heap.c \
	srcs/dongle.c \
	srcs/time.c \
	srcs/monitor.c \
	srcs/sync.c

OBJS = $(SRCS:.c=.o)

HEADERS = headers/codexion.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
