
#ifndef _LEXER_H_
#define _LEXER_H_

typedef enum {
	token_type_literal,
	token_type_empty
} e_token_type;

typedef struct {
	int raw_pos;
	int excerpt_pos;
	char *excerpt;
} s_token_context;

typedef struct s_token {
	e_token_type type;
	char *data;

	s_token_context context;
	struct s_token *next;
} t_token;

t_token *new_token(e_token_type type, char *data);
void delete_token(t_token *token);
t_token *add_token(t_token *root, t_token *token);
t_token *copy_token(t_token *token);
void print_token(t_token *token);

t_token *lex(char *str);

#endif

