
NAME=	../../bin/bnf
SRCS=	$(shell find . -name '*.c')
OBJS=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	cc -o $@ $(OBJS)

%.o: %.c
	cc -c -W -Wall -Werror -Wshadow -pedantic $< -o $@

clean:
	rm -vf $(OBJS)

fclean: clean
	rm -vf $(NAME)

re: fclean all

.PHONY: all clean fclean re

