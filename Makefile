
all: states reader

states:
	make -C states

reader:
	make -C reader

clean: clean_state clean_reader

clean_state:
	make -C states clean

clean_reader:
	make -C reader clean

fclean: fclean_state fclean_reader

fclean_state:
	make -C states fclean

fclean_reader:
	make -C reader fclean

re: fclean all

.PHONY: all states reader clean clean_state clean_reader fclean fclean_state fclean_reader re

