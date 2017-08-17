
NAME=	./bin/ysh

SRCS=	main.c \
		$(shell find . -name '*.c' -not -name 'main.c' -not -path './tests/**' -not -path './demo/**')
OBJS=	$(SRCS:.c=.o)
CC=		cc
CFLAGS=	-g -W -Wall -Werror -Wshadow -pedantic
LDFLAGS= -lreadline

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -vf $(OBJS)

fclean: clean
	rm -vf $(NAME)

re: fclean all

tests: tests_state tests_reader

tests_state:
	make -C states tests

tests_reader:
	make -C reader tests

.PHONY: all states clean fclean re tests tests_state tests_reader

