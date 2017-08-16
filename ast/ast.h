#ifndef _AST_H_
#define _AST_H_

typedef enum {
	node_type_command,
	node_type_literal_string
} e_node_type;

typedef enum {
	value_type_string,
	value_type_integer,
	value_type_undefined
} e_value_type;

typedef union {
	char *string;
	long int integer;
} u_value;

typedef struct {
	e_value_type type;
	u_value value;
} s_value;

typedef struct {
	int raw_pos;
	int excerpt_pos;
	char *excerpt;
} s_node_context;

typedef struct s_node {
	e_node_type type;
	char *data;

	s_value value;
	s_node_context context;
	struct s_node *children;

	struct s_node *next;
} t_node;

t_node *new_node(e_node_type type, char *data);
void delete_node(t_node *node);
t_node *add_node(t_node *root, t_node *node);
void print_node(t_node *node);

#endif
