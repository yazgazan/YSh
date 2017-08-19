
#ifndef _PARSER_H_
#define _PARSER_H_

#include "ast.h"

typedef struct {
	int pos;
	int buf_len;
	char *buf;
	int error;

	int lstart;
} t_parser_context;

typedef int f_class(char);

int peek_one(f_class class, t_parser_context *ctx);
int peek_all(f_class class, t_parser_context *ctx);
int consume_all(f_class class, t_parser_context *ctx);
int consume_one(f_class class, t_parser_context *ctx);
char *read_all(f_class class, t_parser_context *ctx);
t_parser_context *get_line_ctx(t_parser_context *ctx);
void print_ctx_line(t_parser_context *ctx);

t_rule *parse(char *data);

#endif
