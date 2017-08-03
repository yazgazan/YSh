
NAME=	../bin/libreader.so
SRCS=	$(shell find . -name '*.c' -not -path './tests/**' -not -path './demo/**')
OBJS=	$(SRCS:.c=.o)
CC=		cc
CFLAGS=	-g -W -Wall -Wshadow -pedantic -fPIC
LDFLAGS= -L../bin -lstates -lreadline

$(NAME): all

all: $(OBJS)
	$(CC) -shared $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -vf $(OBJS)

fclean: clean
	rm -vf $(NAME)

re: fclean all

demo:
	make -C ./demo run

.PHONY: all clean fclean re demo
