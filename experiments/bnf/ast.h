#ifndef _AST_H_
#define _AST_H_

typedef enum {
	expr_type_and,
	expr_type_or,
	expr_type_group,
	expr_type_lit,
	expr_type_id,
	expr_type_unknown
} e_expr_type;

typedef enum {
	expr_repeat_once,
	expr_repeat_optional,
	expr_repeat_any
} e_expr_repeat;

typedef struct s_expr t_expr;

typedef struct {
	t_expr *exprs;
} t_expr_and;

typedef struct {
	t_expr *exprs;
} t_expr_or;

typedef struct {
	t_expr *exprs;
} t_expr_group;

typedef char *t_expr_lit;
typedef char *t_expr_id;

typedef union {
	t_expr_and and;
	t_expr_or or;
	t_expr_group group;
	t_expr_lit lit;
	t_expr_id id;
} u_expr;

typedef struct s_expr {
	e_expr_type type;
	e_expr_repeat repeat;
	u_expr data;

	struct s_expr *next;
} t_expr;

typedef struct s_rule {
	char *name;

	t_expr *root;
	struct s_rule *next;
} t_rule;

t_rule *new_rule(char *name);
t_rule *add_rule(t_rule *root, t_rule *rule);
void free_rule(t_rule *rule);
void print_rule(t_rule *rule);
void print_rules(t_rule *rules);

t_expr *new_expr();
t_expr *add_expr(t_expr *root, t_expr *expr);
void free_expr(t_expr *expr);
void print_expr(t_expr *expr, char *sep);

#endif

