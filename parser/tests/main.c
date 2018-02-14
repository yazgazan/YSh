
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../lexer.h"
#include "../parser.h"

#define TEST(x) if(x != 0) { printf("FAIL "#x"\n"); failed = 1; } else { printf("OK   "#x"\n"); }

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
		return 1;
	}
	if (tokens->type != token_type_empty) {
		delete_token(tokens);
		return 1;
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
		return 1;
	}
	if (tokens->type != token_type_literal) {
		delete_token(tokens);
		return 1;
	}
	if (tokens->data == NULL)
	{
		delete_token(tokens);
		return 1;
	}
	if (strcmp(expected, tokens->data) != 0)
	{
		delete_token(tokens);
		return 1;
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
			return 1;
		}
		if (token->data == NULL)
		{
			delete_token(tokens);
			return 1;
		}
		if (expected[i] == NULL)
		{
			delete_token(tokens);
			return 1;
		}
		if (strcmp(expected[i], token->data) != 0)
		{
			delete_token(tokens);
			return 1;
		}
		i++;
		token = token->next;
	}

	delete_token(tokens);
	if (expected[i] != NULL)
	{
		return 1;
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

	TEST(test_lexer_empty(""));
	TEST(test_lexer_empty(" "))
	TEST(test_lexer_empty("  "))
	TEST(test_lexer_empty("\r"))
	TEST(test_lexer_empty("\n"))
	TEST(test_lexer_empty("\t"))
	TEST(test_lexer_empty("\r\n "))

	TEST(test_lexer_n_lit(singlelit("foo"), "foo"));
	TEST(test_lexer_n_lit(singlelit("b"), " b"));
	TEST(test_lexer_n_lit(singlelit("hello"), "hello "));
	TEST(test_lexer_n_lit(singlelit("foo"), " \tfoo \n"));

	TEST(test_lexer_n_lit(twolits("foo", "bar"), "foo \tbar"));
	TEST(test_lexer_n_lit(twolits("b", "f"), " b\nf"));
	TEST(test_lexer_n_lit(twolits("hello", "world"), "hello \tworld   "));
	TEST(test_lexer_n_lit(twolits("foo", "bar"), " \tfoo \nbar"));
}

int test_parser_null()
{
	t_node *ast;

	ast = parse(NULL);

	if (ast != NULL)
	{
		return 1;
	}

	return 0;
}

int test_parser_empty(char *s)
{
	t_token *tokens;
	t_node *ast;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}
	ast = parse(tokens);

	if (ast != NULL)
	{
		return 1;
	}

	return 0;
}

int test_parser_simple_cmd(char *expect, char *s)
{
	t_token *tokens;
	t_node *ast;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}
	ast = parse(tokens);

	if (ast == NULL)
	{
		return 1;
	}
	if (ast->type != node_type_command)
	{
		return 1;
	}
	if (strcmp(expect, ast->data) != 0)
	{
		return 1;
	}
	if (ast->next != NULL || ast->children != NULL)
	{
		return 1;
	}

	return 0;
}

int test_parser_one_arg_cmd(char *cmd, char *arg, char *s)
{
	t_token *tokens;
	t_node *ast;

	tokens = lex(s);
	if (tokens == NULL)
	{
		return 1;
	}
	ast = parse(tokens);

	if (ast == NULL)
	{
		return 1;
	}
	if (ast->type != node_type_command)
	{
		return 1;
	}
	if (strcmp(cmd, ast->data) != 0)
	{
		return 1;
	}
	if (ast->next != NULL || ast->children == NULL)
	{
		return 1;
	}
	if (strcmp(arg, ast->children->data) != 0)
	{
		return 1;
	}
	if (ast->children->next != NULL || ast->children->children != NULL)
	{
		return 1;
	}

	return 0;
}

void test_parser()
{
	printf("Running parser tests...\n");

	TEST(test_parser_null());

	TEST(test_parser_empty(""));
	TEST(test_parser_empty("  "));
	TEST(test_parser_empty("\n"));

	TEST(test_parser_simple_cmd("foo", "foo"));
	TEST(test_parser_simple_cmd("foo", "  foo"));
	TEST(test_parser_simple_cmd("foo", " foo\r\n"));
	TEST(test_parser_simple_cmd("f", "f"));

	TEST(test_parser_one_arg_cmd("foo", "bar", "foo bar"));
	TEST(test_parser_one_arg_cmd("foo", "bar", "  foo  bar \n"));
	TEST(test_parser_one_arg_cmd("foo", "bar", " foo\r\nbar\n")); /* should fail in the future */
	TEST(test_parser_one_arg_cmd("f", "b", "f b"));
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
