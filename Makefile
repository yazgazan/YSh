
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
	find . -name '*.o' -exec rm -v {} \;

fclean: clean fclean_state fclean_reader fclean_parser
	rm -vf $(NAME)

re: fclean all

tests: tests_state tests_reader tests_parser

fclean_state:
	make -C states fclean

tests_state:
	make -C states tests

fclean_reader:
	make -C reader fclean

tests_reader:
	make -C reader tests

fclean_parser:
	make -C parser fclean

tests_parser:
	make -C parser tests

.PHONY: all states clean fclean re tests fclean_sta tests_state fclean_reader tests_reader fclean_parser tests_parser

