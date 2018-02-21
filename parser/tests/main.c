
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lexer.h"
#include "../parser.h"

#define TEST(x) if(x != 0) { printf("FAIL [%d] "#x"\n", x); failed = 1; } else { printf("OK   "#x"\n"); }

static char *copystr(char *src);
void test_lexer();
void test_parser();

int failed = 0;

int main(void)
{
	printf("Running tests...\n\n");

	test_lexer();
	test_parser();

	printf("\n");

	return failed;
}

int test_lexer_empty(char *s)
{
	t_token *tokens;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}
	if (tokens->next != NULL)
	{
		delete_token(tokens);
		return 2;
	}
	if (tokens->type != token_type_empty) {
		delete_token(tokens);
		return 3;
	}

	delete_token(tokens);
	return 0;
}

int test_lexer_single_lit(char *expected, char *s)
{
	t_token *tokens;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}
	if (tokens->next != NULL)
	{
		delete_token(tokens);
		return 2;
	}
	if (tokens->type != token_type_literal) {
		delete_token(tokens);
		return 3;
	}
	if (tokens->data == NULL)
	{
		delete_token(tokens);
		return 4;
	}
	if (strcmp(expected, tokens->data) != 0)
	{
		delete_token(tokens);
		return 5;
	}

	delete_token(tokens);
	return 0;
}

int test_lexer_n_lit(char **expected, char *s)
{
	t_token *tokens;
	t_token *token;
	int i;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}

	i = 0;
	token = tokens;
	while (token != NULL)
	{
		if (token->type != token_type_literal) {
			delete_token(tokens);
			return 10;
		}
		if (token->data == NULL)
		{
			delete_token(tokens);
			return 11;
		}
		if (expected[i] == NULL)
		{
			delete_token(tokens);
			return 12;
		}
		if (strcmp(expected[i], token->data) != 0)
		{
			delete_token(tokens);
			return 13;
		}
		i++;
		token = token->next;
	}

	delete_token(tokens);
	if (expected[i] != NULL)
	{
		return 20;
	}
	return 0;
}

char **singlelit(char *lit)
{
	char **lits;

	lits = calloc(2, sizeof(char*));

	lits[0] = copystr(lit);

	return lits;
}
char **twolits(char *first, char *second)
{
	char **lits;

	lits = calloc(3, sizeof(char*));

	lits[0] = copystr(first);
	lits[1] = copystr(second);

	return lits;
}

void test_lexer()
{
	printf("Running lexer tests...\n");

	TEST(test_lexer_empty(""))
	TEST(test_lexer_empty(" "))
	TEST(test_lexer_empty("  "))
	TEST(test_lexer_empty("\r"))
	TEST(test_lexer_empty("\n"))
	TEST(test_lexer_empty("\t"))
	TEST(test_lexer_empty("\r\n "))

	TEST(test_lexer_n_lit(singlelit("foo"), "foo"))
	TEST(test_lexer_n_lit(singlelit("b"), " b"))
	TEST(test_lexer_n_lit(singlelit("hello"), "hello "))
	TEST(test_lexer_n_lit(singlelit("foo"), " \tfoo \n"))

	TEST(test_lexer_n_lit(twolits("foo", "bar"), "foo \tbar"))
	TEST(test_lexer_n_lit(twolits("b", "f"), " b\nf"))
	TEST(test_lexer_n_lit(twolits("hello", "world"), "hello \tworld   "))
	TEST(test_lexer_n_lit(twolits("foo", "bar"), " \tfoo \nbar"))
}

int test_parser_naked_command(char *expected, char *s)
{
	t_token *tokens;
	t_node *nodes;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}

	nodes = parse(tokens);
	if (nodes == NULL)
	{
		delete_token(tokens);
		return 2;
	}

	if (count_nodes(nodes) != 1)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 3;
	}
	if (nodes->type != node_type_command)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 4;
	}
	if (nodes->data == NULL)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 5;
	}
	if (strcmp(expected, nodes->data) != 0)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 6;
	}

	delete_node(nodes);
	delete_token(tokens);

	return 0;
}

int test_parser_n_args(char *expected_cmd, char **expected_args, char *s)
{
	t_token *tokens;
	t_node *nodes;
	t_node *node;
	int i;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}

	nodes = parse(tokens);
	if (nodes == NULL)
	{
		return 2;
	}

	if (count_nodes(nodes) != 1)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 1;
	}
	if (nodes->type != node_type_command)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 4;
	}
	if (nodes->data == NULL)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 5;
	}
	if (strcmp(expected_cmd, nodes->data) != 0)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 6;
	}
	if (nodes->children == NULL)
	{
		delete_node(nodes);
		delete_token(tokens);
		return 7;
	}

	i = 0;
	node = nodes->children;
	while (node != NULL)
	{
		if (node->type != node_type_literal_string)
		{
			delete_node(nodes);
			delete_token(tokens);
			return 20;
		}
		if (node->data == NULL)
		{
			delete_node(nodes);
			delete_token(tokens);
			return 21;
		}
		if (strcmp(expected_args[i], node->data) != 0)
		{
			delete_node(nodes);
			delete_token(tokens);
			return 22;
		}

		node = node->next;
		i++;
	}

	if (expected_args[i] != NULL)
	{
			delete_node(nodes);
			delete_token(tokens);
			return 40;
	}
	delete_node(nodes);
	delete_token(tokens);

	return 0;
}

void test_parser()
{
	printf("\nRunning parser tests...\n");

	TEST(test_parser_naked_command("cmd", "cmd"))
	TEST(test_parser_n_args("cmd", singlelit("arg"), "cmd arg"))
	TEST(test_parser_n_args("cmd", twolits("arg1", "arg2"), "cmd arg1 arg2"))
}

static char *copystr(char *src)
{
	char *dst;
	int len;

	if (src == NULL)
	{
		return NULL;
	}
	len = strlen(src);
	dst = calloc(len+1, sizeof(*dst));
	if (dst == NULL)
	{
		return NULL;
	}

	return strncpy(dst, src, len);
}
