NAME = codexion

CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread

SRCS = srcs/codexion.c \
	srcs/parsing.c \
	srcs/coder.c \
	srcs/utils.c \
	srcs/action.c \
	srcs/process.c \
	srcs/request.c

OBJS = srcs/codexion.o \
	srcs/parsing.o \
	srcs/coder.o \
	srcs/utils.o \
	srcs/action.o \
	srcs/process.o \
	srcs/request.o

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

srcs/codexion.o: srcs/codexion.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/codexion.c -o srcs/codexion.o

srcs/parsing.o: srcs/parsing.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/parsing.c -o srcs/parsing.o

srcs/coder.o: srcs/coder.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/coder.c -o srcs/coder.o

srcs/utils.o: srcs/utils.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/utils.c -o srcs/utils.o

srcs/action.o: srcs/action.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/action.c -o srcs/action.o

srcs/process.o: srcs/process.c headers/codexion.h headers/parsing.h headers/utils.h headers/coder.h headers/action.h
	$(CC) $(CFLAGS) -c srcs/process.c -o srcs/process.o

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
