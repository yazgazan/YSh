
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "lexer.h"

static char *copystr(char *src);
static char *copysubstr(char *src, int start, int end);

t_token *new_token(e_token_type type, char *data)
{
	t_token *token;

	token = malloc(sizeof(*token));
	if (token == NULL)
	{
		return NULL;
	}

	token->type = type;
	token->next = NULL;
	token->data = copystr(data);
	if (token->data == NULL)
	{
		free(token);
		return NULL;
	}

	return token;
}

void delete_token(t_token *token)
{
	if (token->next != NULL)
	{
		delete_token(token->next);
	}

	free(token->data);
	free(token);
}

t_token *add_token(t_token *root, t_token *token)
{
	t_token *cur;

	if (root == NULL)
	{
		return token;
	}

	cur = root;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = token;

	return root;
}

t_token *copy_token(t_token *token)
{
	t_token *ret;

	ret = malloc(sizeof(*ret));
	if (ret == NULL)
	{
		return ret;
	}
	ret->type = token->type;
	ret->data = copystr(ret->data);
	if (ret->data == NULL)
	{
		free(ret);
		return NULL;
	}
	ret->context.raw_pos = token->context.raw_pos;
	ret->context.excerpt_pos = token->context.excerpt_pos;
	ret->context.excerpt = copystr(token->context.excerpt);
	if (ret->context.excerpt == NULL)
	{
		free(ret->data);
		free(ret);
		return NULL;
	}
	ret->next = NULL;

	return ret;
}

void print_token(t_token *token)
{
	switch (token->type) {
		case token_type_literal:
			printf("(%s)", token->data);
			break;
		default:
			printf("<unknown type (%s)>", token->data);
			break;
	}

	if (token->next != NULL)
	{
		printf(" ");
		print_token(token->next);
	} else {
		printf("\n");
	}
}

int is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r')
	{
		return 1;
	}

	return 0;
}

int lex_read_whitespace(char *str, int pos)
{
	int i;

	i = 0;
	while (str[pos+i] != '\0')
	{
		if (is_whitespace(str[pos+i]) == 1) {
			i++;
			continue;
		}
		if (i == 0)
		{
			return -1;
		}
		return pos+i;
	}

	return pos+i;
}

int lex_read_literal(char *str, int pos)
{
	int i;

	i = 0;
	while (str[pos+i] != '\0')
	{
		if (is_whitespace(str[pos+i]) == 0) {
			i++;
			continue;
		}
		if (i == 0)
		{
			return -1;
		}

		return pos+i;
	}

	if (i == 0)
	{
		return -1;
	}
	return pos+i;
}

int lex_read_EOF(char *str, int pos)
{
	if (str[pos] == '\0')
	{
		return pos;
	}

	return -1;
}

t_token *lex(char *str)
{
	int i;
	t_token *root;

	root = NULL;
	i = lex_read_whitespace(str, 0);
	if (i == -1)
	{
		i = 0;
	}
	while (lex_read_EOF(str, i) == -1)
	{
		t_token *token;
		char *data;
		int new;

		new = lex_read_literal(str, i);
		if (new <= 0)
		{
			// TODO(yazgazan): error managment
			printf("error: no literal to read at %d\n", i);
			return root;
		}
		data = copysubstr(str, i, new);
		if (data == NULL)
		{
			// TODO(yazgazan): error managment
			printf("error: failed to copy substr (start = %d, end = %d)\n", i, new);
			return root;
		}
		token = new_token(token_type_literal, data);
		free(data);
		token->context.raw_pos = i;
		// TODO(yazgazan): excerpt
		token->context.excerpt_pos = 0;
		token->context.excerpt = NULL;

		root = add_token(root, token);
		i = new;

		new = lex_read_whitespace(str, i);
		if (new != -1)
		{
			i = new;
		}
	}

	return root;
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
	dst = malloc(sizeof(*dst) * len + 1);
	if (dst == NULL)
	{
		return NULL;
	}

	return strncpy(dst, src, len);
}

static char *copysubstr(char *src, int start, int end)
{
	char *dst;
	int len;

	if (start >= end)
	{
		return NULL;
	}
	len = end - start;

	dst = malloc(sizeof(*dst) * len + 1);
	if (dst == NULL)
	{
		return NULL;
	}

	dst = strncpy(dst, src + start, len);
	dst[len] = '\0';

	return dst;
}

