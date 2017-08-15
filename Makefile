
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

tests: tests_state tests_reader

tests_state:
	make -C states tests

tests_reader:
	make -C reader tests

.PHONY: all states reader clean clean_state clean_reader fclean fclean_state fclean_reader re tests tests_state tests_reader

