NAME=	parser-tests
SRCS=	main.c \
		$(shell find .. -name '*.c' -not -name 'main.c') \
		$(shell find ../../ast -name '*.c' -not -name 'main.c')
OBJS=	$(SRCS:.c=.o)
CC=		cc
CFLAGS=	-g -W -Wall -Werror -Wshadow -pedantic
LDFLAGS=

$(NAME): all

all: $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -vf $(OBJS)

fclean: clean
	rm -vf $(NAME)

re: fclean all

run: all
	./$(NAME)

.PHONY: all clean fclean re
