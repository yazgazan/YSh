
#include <stdlib.h>

#include <readline/readline.h>

#include "reader.h"
#include "../states/states.h"

// TODO(yazgazan): add tests
char *read_command(t_state *state)
{
	char *s;

	// TODO(yazgazan): get prompt from state->environ
	s = readline("> ");
	if (s == NULL) {
		state->exiting = EXITING;
		return NULL;
	}

	return s;
}
