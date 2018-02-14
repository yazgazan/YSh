
#include <stdlib.h>
#include <stdio.h>

#include "ast.h"
#include "utils.h"

t_rule *new_rule(char *name)
{
	t_rule *rule;

	rule = calloc(1, sizeof(*rule));
	if (rule == NULL)
	{
		return NULL;
	}

	rule->name = copystr(name);
	if (rule->name == NULL)
	{
		free(rule);
		return NULL;
	}

	rule->root = NULL;
	rule->next = NULL;

	return rule;
}

t_expr *new_expr()
{
	t_expr *expr;

	expr = calloc(1, sizeof(*expr));
	if (expr == NULL)
	{
		return NULL;
	}
	expr->type = expr_type_unknown;
	expr->next = NULL;
	expr->repeat = expr_repeat_once;

	return expr;
}

t_expr *add_expr(t_expr *root, t_expr *expr)
{
	t_expr *cur;

	if (root == NULL)
	{
		return expr;
	}
	cur = root;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = expr;

	return root;
}

void free_expr(t_expr *expr)
{
	if (expr == NULL)
	{
		return;
	}
	/* TODO(yazgazan): free expr->data */
	if (expr->next != NULL)
	{
		free_expr(expr->next);
	}
	free(expr);
}

t_rule *add_rule(t_rule *root, t_rule *rule)
{
	t_rule *cur;

	if (root == NULL)
	{
		return rule;
	}
	cur = root;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}

	cur->next = rule;

	return root;
}


void free_rule(t_rule *rule)
{
	if (rule == NULL)
	{
		return;
	}

	free(rule->name);
	if (rule->root != NULL)
	{
		free_expr(rule->root);
	}
	if (rule->next != NULL)
	{
		free_rule(rule->next);
	}
	free(rule);
}

void print_expr(t_expr *expr, char *sep)
{
	switch (expr->type)
	{
		case expr_type_lit:
			printf("\"%s\"", expr->data.lit);
			break;
		case expr_type_id:
			printf("%s", expr->data.id);
			break;
		case expr_type_and:
			print_expr(expr->data.and.exprs, " ");
			break;
		case expr_type_or:
			print_expr(expr->data.or.exprs, " | ");
			break;
		case expr_type_group:
			printf("(");
			print_expr(expr->data.or.exprs, "");
			printf(")");
			break;
		case expr_type_unknown:
			printf("<unknown>");
			break;
	}

	switch (expr->repeat)
	{
		case expr_repeat_any:
			printf("*");
			break;
		case expr_repeat_optional:
			printf("?");
			break;
		case expr_repeat_once:
			break;
	}

	if (expr->next != NULL)
	{
		printf("%s", sep);
		print_expr(expr->next, sep);
	}
}

void print_rule(t_rule *rule)
{
	printf("%s: ", rule->name);
	print_expr(rule->root, "");
	printf(";\n");
}

void print_rules(t_rule *rules)
{
	while (rules != NULL)
	{
		print_rule(rules);
		printf("\n");
		rules = rules->next;
	}
}

