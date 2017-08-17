
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "./reader/reader.h"
#include "./states/states.h"
#include "./parser/parser.h"
#include "./interpreter/interpreter.h"

int main(void)
{
	char *s;
	t_state *state;
	t_token *tokens;
	t_node *ast;

	state = new_state();
	if (state == NULL) {
		return 1;
	}
	init_from_env(state);

	while (42) {
		s = read_command(state);
		if (state->exiting == EXITING) {
			printf("exiting...\n");
			break;
		}
		tokens = lex(s);
		if (tokens == NULL)
		{
			printf("failed to lex\n");
			delete_state(state);
			free(s);
			return 1;
		}
		if (tokens->type == token_type_empty)
		{
			delete_token(tokens);
			free(s);
			continue;
		}
		ast = parse(tokens);
		if (ast == NULL)
		{
			printf("failed to parse\n");
			delete_token(tokens);
			delete_state(state);
			free(s);
			return 1;
		}
		if (interpret(state, ast) != 0)
		{
			printf("failed to interpret\n");
			delete_token(tokens);
			delete_node(ast);
			delete_state(state);
			free(s);
			return 1;
		}

		delete_token(tokens);
		delete_node(ast);
		free(s);
	}

	delete_state(state);
	free(s);
	return 0;
}

