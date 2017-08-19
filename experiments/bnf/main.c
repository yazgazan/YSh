
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "parser.h"

static size_t file_size(int fd)
{
	off_t offset;

	offset = lseek(fd, 0, SEEK_END);
	if (offset == -1)
	{
		perror("reading input file");
		return -1;
	}

	if (lseek(fd, 0, SEEK_SET) == -1)
	{
		perror("reading input file");
		return -1;
	}

	return offset;
}

static char *read_file(char *fname)
{
	int fd;
	off_t fsize;
	char *content;

	fd = open(fname, O_RDONLY);
	if (fd == -1)
	{
		perror("opening input file");
		return NULL;
	}

	fsize = file_size(fd);
	if (fsize == -1)
	{
		close(fd);
		return NULL;
	}
	content = calloc(fsize+1, sizeof(*content));
	if (content == NULL)
	{
		return NULL;
	}

	if (read(fd, content, fsize) == -1)
	{
		perror("reading input file");
		free(content);
		close(fd);
		return NULL;
	}

	close(fd);
	return content;
}

int main(int argc, char *argv[])
{
	t_rule *rules;
	char *bnf_file;

	if (argc != 2)
	{
		printf("Usage: %s <bnf file>\n", argv[0]);
		return 2;
	}

	bnf_file = read_file(argv[1]);
	if (bnf_file == NULL)
	{
		return 1;
	}

	rules = parse(bnf_file);
	if (rules == NULL)
	{
		free(bnf_file);
		return 1;
	}

	print_rules(rules);
	return 0;
}

