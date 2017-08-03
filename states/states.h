
#ifndef _STATES_H_
#define _STATES_H_

typedef enum {
	NOT_EXITING,
	EXITING
} e_exiting;

typedef struct s_value {
	char *name;
	char *value;
	struct s_value *next;
} t_value;

typedef struct s_scope {
	char *id;
	t_value *variables;
	struct s_scope *next;
} t_scope;

typedef struct {
	t_value *environ;
	t_scope *variables;
	int last_exit_code;
	e_exiting exiting;
} t_state;

t_state *new_state(void);
void init_from_env(t_state *state);
void delete_state(t_state *state);
void print_state(t_state *state);

t_scope *create_scope(t_scope *scopes, char *id);
void delete_scopes(t_scope *scopes);
t_scope *get_scope(t_scope *scopes, char *id);
void print_scopes(t_scope *scopes);

t_value *create_value(t_value *values, char *name, char *value);
void delete_values(t_value *values);
t_value *get_value(t_value *values, char *name);
t_value *set_value(t_value *values, char *name, char *value);
void print_values(t_value *values);

char *exiting_string(e_exiting state);

#endif
