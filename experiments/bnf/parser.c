
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"
#include "parser.h"
#include "utils.h"

static t_expr *read_expr_atomic_repeat(t_parser_context *ctx);
static t_expr *read_expr_repeat(t_parser_context *ctx);

static int is_whitespace(char c)
{
	switch (c)
	{
		case ' ':
		case '\t':
		case '\n':
		case '\r':
			return 1;
	}

	return 0;
}

static int is_newline(char c)
{
	switch (c)
	{
		case '\r':
		case '\n':
			return 1;
	}

	return 0;
}

static int is_not_newline(char c)
{
	switch (c)
	{
		case '\r':
		case '\n':
			return 0;
	}

	return 1;
}

static int is_hash(char c)
{
	if (c == '#')
	{
		return 1;
	}

	return 0;
}

static int is_qmark(char c)
{
	if (c == '?')
	{
		return 1;
	}

	return 0;
}

static int is_pipe(char c)
{
	if (c == '|')
	{
		return 1;
	}

	return 0;
}

static int is_opar(char c)
{
	if (c == '(')
	{
		return 1;
	}

	return 0;
}

static int is_cpar(char c)
{
	if (c == ')')
	{
		return 1;
	}

	return 0;
}

static int is_star(char c)
{
	if (c == '*')
	{
		return 1;
	}

	return 0;
}

static int is_id(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'A'))
	{
		return 1;
	}
	if (c >= '9' && c <= '9')
	{
		return 1;
	}
	if (c == '_')
	{
		return 1;
	}

	return 0;
}

static int is_colon(char c)
{
	if (c == ':')
	{
		return 1;
	}

	return 0;
}

static int is_semicolon(char c)
{
	if (c == ';')
	{
		return 1;
	}

	return 0;
}

static int is_dblquote(char c)
{
	if (c == '"')
	{
		return 1;
	}

	return 0;
}

static int is_not_dblquote(char c)
{
	if (c == '"')
	{
		return 0;
	}

	return 1;
}

int peek_one(f_class class, t_parser_context *ctx)
{
	if (ctx->pos >= ctx->buf_len)
	{
		return 0;
	}

	return class(ctx->buf[ctx->pos]);
}

int peek_all(f_class class, t_parser_context *ctx)
{
	int i;

	if (ctx->pos >= ctx->buf_len)
	{
		return 0;
	}
	i = ctx->pos;
	while (i < ctx->buf_len)
	{
		if (class(ctx->buf[i]) == 0)
		{
			break;
		}

		i++;
	}

	return i - ctx->pos;
}

int consume_all(f_class class, t_parser_context *ctx)
{
	int n;

	n = peek_all(class, ctx);

	ctx->pos += n;

	return n;
}

static int consume_comment(t_parser_context *ctx)
{
	int start;

	start = ctx->pos;
	if (consume_all(is_hash, ctx) == 0)
	{
		return 0;
	}

	consume_all(is_not_newline, ctx);
	if (consume_all(is_newline, ctx) == 0)
	{
		ctx->pos = start;
		return 0;
	}

	return ctx->pos - start;
}

/* by nothingness, understand whitespaces and comments */
static int consume_nothingness(t_parser_context *ctx)
{
	int total;
	int n;

	total = 0;
	n = -1;
	while (n != 0)
	{
		n = consume_all(is_whitespace, ctx);
		n += consume_comment(ctx);
		total += n;
	}

	return total;
}

int consume_one(f_class class, t_parser_context *ctx)
{
	int n;

	n = peek_one(class, ctx);

	ctx->pos += n;

	return n;
}

char *read_all(f_class class, t_parser_context *ctx)
{
	int start, n;
	char *chunk;

	start = ctx->pos;
	n = consume_all(class, ctx);
	if (n == 0)
	{
		return NULL;
	}
	chunk = copysubstr(ctx->buf, start, ctx->pos);
	if (chunk == NULL)
	{
		ctx->pos = start;
		return NULL;
	}

	return chunk;
}

static t_expr *read_literal(t_parser_context *ctx)
{
	t_expr *expr;
	char *str;
	int start;

	start = ctx->pos;
	if (consume_one(is_dblquote, ctx) == 0)
	{
		return NULL;
	}
	str = read_all(is_not_dblquote, ctx);
	if (str == NULL)
	{
		printf("unexpected empty literal\n");
		ctx->error = 1;
		ctx->pos = start;
		return NULL;
	}
	expr = new_expr();
	if (expr == NULL)
	{
		printf("unexpected error");
		ctx->error = 1;
		ctx->pos = start;
		free(str);
		return NULL;
	}
	expr->type = expr_type_lit;
	expr->data.lit = str;

	if (consume_one(is_dblquote, ctx) == 0)
	{
		printf("expected closing '\"'\n");
		ctx->error = 1;
		ctx->pos = start;
		free(str);
		return NULL;
	}

	return expr;
}

static t_expr *read_id(t_parser_context *ctx)
{
	t_expr *expr;
	char *str;
	int start;

	start = ctx->pos;

	str = read_all(is_id, ctx);
	if (str == NULL)
	{
		return NULL;
	}
	expr = new_expr();
	if (expr == NULL)
	{
		printf("unexpected error");
		ctx->error = 1;
		ctx->pos = start;
		free(str);
		return NULL;
	}
	expr->type = expr_type_id;
	expr->data.id = str;

	return expr;
}

static t_expr *read_expr_atomic(t_parser_context *ctx)
{
	t_expr *expr;

	expr = read_literal(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	expr = read_id(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	return NULL;
}

t_parser_context *get_line_ctx(t_parser_context *ctx)
{
	t_parser_context *newctx;
	int i;
	int lno;
	int lpos;
	int lstart;
	int lend;

	newctx = calloc(1, sizeof(*newctx));
	if (newctx == NULL)
	{
		return NULL;
	}

	i = 0;
	lno = 0;
	lpos = 0;
	lstart = 0;
	while (i < ctx->pos)
	{
		if (is_newline(ctx->buf[i]))
		{
			lno++;
			lstart = i+1;
			lpos = 0;
		}
		lpos++;
		i++;
	}
	lend = 0;
	i = lstart + lpos;
	while (i < ctx->buf_len)
	{
		if (is_newline(ctx->buf[i]))
		{
			lend = i;
			break;
		}
		i++;
	}
	newctx->buf = copysubstr(ctx->buf, lstart, lend);
	newctx->buf_len = lend - lstart;
	newctx->pos = lpos;
	newctx->lstart = lno;

	return newctx;
}

void print_ctx_line(t_parser_context *ctx)
{
	t_parser_context *lctx;
	int i;

	lctx = get_line_ctx(ctx);
	if (lctx == NULL)
	{
		printf("Error: cannot get line context");
		return;
	}

	printf("at %d:%d\n", lctx->lstart+1, lctx->pos+1);
	printf("%s\n", lctx->buf);
	i = 0;
	while (i+1 < lctx->pos)
	{
		printf(" ");
		i++;
	}
	printf("^\n");
	free(lctx->buf);
	free(lctx);
}

static t_expr *read_and(t_parser_context *ctx)
{
	int start;
	t_expr *lhs;
	t_expr *and;

	start = ctx->pos;
	consume_nothingness(ctx);
	lhs = read_expr_atomic_repeat(ctx);
	if (lhs == NULL)
	{
		ctx->pos = start;
		return NULL;
	}

	consume_nothingness(ctx);
	lhs->next = read_expr_repeat(ctx);
	if (lhs->next == NULL)
	{
		ctx->pos = start;
		free_expr(lhs);
		return NULL;
	}

	and = new_expr();
	if (and == NULL)
	{
		printf("unexpected error\n");
		ctx->error = 1;
		free_expr(lhs);
		return NULL;
	}
	and->type = expr_type_and;
	and->data.and.exprs = lhs;


	return and;
}

static t_expr *read_group(t_parser_context *ctx)
{
	int start;
	t_expr *expr;
	t_expr *group;

	start = ctx->pos;
	consume_nothingness(ctx);
	if (consume_one(is_opar, ctx) != 1)
	{
		ctx->pos = start;
		return NULL;
	}

	consume_nothingness(ctx);
	expr = read_expr_repeat(ctx);
	if (expr == NULL)
	{
		ctx->pos = start;
		return NULL;
	}

	consume_nothingness(ctx);
	if (consume_one(is_cpar, ctx) != 1)
	{
		ctx->pos = start;
		free_expr(expr);
		return NULL;
	}

	group = new_expr();
	if (group == NULL)
	{
		printf("unexpected error\n");
		ctx->error = 1;
		free_expr(expr);
		return NULL;
	}
	group->type = expr_type_group;
	group->data.group.exprs = expr;


	return group;
}

static t_expr *read_or(t_parser_context *ctx)
{
	int start;
	t_expr *lhs;
	t_expr *or;

	start = ctx->pos;
	consume_nothingness(ctx);
	lhs = read_expr_atomic_repeat(ctx);
	if (lhs == NULL)
	{
		ctx->pos = start;
		return NULL;
	}

	consume_nothingness(ctx);
	if (consume_one(is_pipe, ctx) != 1)
	{
		ctx->pos = start;
		return NULL;
	}
	consume_nothingness(ctx);

	lhs->next = read_expr_repeat(ctx);
	if (lhs->next == NULL)
	{
		ctx->pos = start;
		free_expr(lhs);
		return NULL;
	}

	or = new_expr();
	if (or == NULL)
	{
		printf("unexpected error\n");
		ctx->error = 1;
		free_expr(lhs);
		return NULL;
	}
	or->type = expr_type_or;
	or->data.or.exprs = lhs;


	return or;
}

static t_expr *read_expr_group(t_parser_context *ctx)
{
	t_expr *expr;
	int start;

	start = ctx->pos;

	expr = read_group(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			ctx->pos = start;
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	expr = read_or(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			ctx->pos = start;
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	expr = read_and(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			ctx->pos = start;
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	expr = read_expr_atomic(ctx);
	if (ctx->error)
	{
		if (expr != NULL)
		{
			ctx->pos = start;
			free_expr(expr);
		}
		return NULL;
	}
	if (expr != NULL)
	{
		return expr;
	}

	return NULL;
}

static t_expr *read_expr_repeat(t_parser_context *ctx)
{
	t_expr *expr;

	expr = read_expr_group(ctx);
	if (expr == NULL)
	{
		return NULL;
	}
	expr->repeat = expr_repeat_once;

	if (consume_one(is_qmark, ctx) == 1)
	{
		expr->repeat = expr_repeat_optional;
	}
	else if (consume_one(is_star, ctx) == 1)
	{
		expr->repeat = expr_repeat_any;
	}

	return expr;
}

static t_expr *read_expr_atomic_repeat(t_parser_context *ctx)
{
	t_expr *expr;

	expr = read_expr_atomic(ctx);
	if (expr == NULL)
	{
		return NULL;
	}
	expr->repeat = expr_repeat_once;

	if (consume_one(is_qmark, ctx) == 1)
	{
		expr->repeat = expr_repeat_optional;
	}
	else if (consume_one(is_star, ctx) == 1)
	{
		expr->repeat = expr_repeat_any;
	}

	return expr;
}

static t_rule *read_rule(t_parser_context *ctx)
{
	t_rule *rule;
	char *id;
	int start;

	start = ctx->pos;

	id = read_all(is_id, ctx);
	if (id == NULL)
	{
		printf("expected id\n");
		ctx->error = 1;
		ctx->pos = start;
		return NULL;
	}

	rule = new_rule(id);
	free(id);

	if (rule == NULL)
	{
		ctx->pos = start;
		return NULL;
	}

	consume_nothingness(ctx);
	if (consume_one(is_colon, ctx) == 0)
	{
		printf("expected ':', got '%c' instead\n", ctx->buf[ctx->pos]);
		ctx->error = 1;
		ctx->pos = start;
		free_rule(rule);
		return NULL;
	}

	consume_nothingness(ctx);
	rule->root = read_expr_repeat(ctx);
	if (rule->root == NULL)
	{
		printf("expected expression:\n");
		print_ctx_line(ctx);
		ctx->error = 1;
		free_rule(rule);
		ctx->pos = start;
		return NULL;
	}


	consume_nothingness(ctx);
	if (consume_one(is_semicolon, ctx) == 0)
	{
		printf("expected ';', got '%c' instead\n", ctx->buf[ctx->pos]);
		print_ctx_line(ctx);
		ctx->error = 1;
		ctx->pos = start;
		free_rule(rule);
		return NULL;
	}

	return rule;
}

static t_rule *read_rules(t_parser_context *ctx)
{
	t_rule *rules;
	t_rule *rule;
	int start;

	start = ctx->pos;
	rules = NULL;
	while (ctx->pos < ctx->buf_len)
	{
		consume_nothingness(ctx);
		rule = read_rule(ctx);
		if (rule == NULL)
		{
			free_rule(rules);
			ctx->pos = start;
			return NULL;
		}
		rules = add_rule(rules, rule);
		consume_nothingness(ctx);
	}

	return rules;
}

t_rule *parse(char *data)
{
	t_parser_context ctx;

	ctx.pos = 0;
	ctx.buf = data;
	ctx.buf_len = strlen(data);
	ctx.error = 0;
	ctx.lstart = 0;

	return read_rules(&ctx);
}
