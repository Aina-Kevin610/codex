NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread
CPPFLAGS = -Iheaders

SRCS = srcs/codexion.c \
	srcs/parsing.c \
	srcs/parsing_utils.c

OBJS = srcs/codexion.o \
	srcs/parsing.o \
	srcs/parsing_utils.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

srcs/codexion.o: srcs/codexion.c headers/codexion.h headers/parsing.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c srcs/codexion.c -o srcs/codexion.o

srcs/parsing.o: srcs/parsing.c headers/codexion.h headers/parsing.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c srcs/parsing.c -o srcs/parsing.o

srcs/parsing_utils.o: srcs/parsing_utils.c headers/codexion.h headers/parsing.h
	$(CC) $(CFLAGS) $(CPPFLAGS) -c srcs/parsing_utils.c -o srcs/parsing_utils.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
