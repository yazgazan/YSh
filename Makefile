
NAME=	./bin/ysh

SRCS=	main.c \
		$(shell find . -name '*.c' -not -name 'main.c' -not -path './tests/**' -not -path './demo/**')
OBJS=	$(SRCS:.c=.o)
CC=		cc
CFLAGS=	-g -W -Wall -Werror -Wshadow -pedantic
LDFLAGS= -lreadline

all: $(NAME) states reader parser

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

states:
	make -C states

reader:
	make -C reader

parser:
	make -C parser

clean: clean_ysh clean_state clean_reader clean_parser

clean_ysh:
	rm -vf $(OBJS)

clean_state:
	make -C states clean

clean_reader:
	make -C reader clean

clean_parser:
	make -C parser clean

fclean: fclean_ysh fclean_state fclean_reader fclean_parser

fclean_ysh: clean_ysh
	rm -vf $(NAME)

fclean_state:
	make -C states fclean

fclean_reader:
	make -C reader fclean

fclean_parser:
	make -C parser fclean

re: fclean all

tests: tests_state tests_reader

tests_state:
	make -C states tests

tests_reader:
	make -C reader tests

.PHONY: all states reader parser clean clean_ysh clean_state clean_reader clean_parser fclean fclean_ysh fclean_state fclean_reader fclean_parse re tests tests_state tests_reader

