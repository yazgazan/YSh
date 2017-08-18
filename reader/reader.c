
#include <stdlib.h>

#include <readline/readline.h>

#include "reader.h"
#include "../states/states.h"

char *g_default_prompt = "> ";
char *g_prompt_key = "PS1";
static char *get_prompt(t_state *state);

void init_reader()
{
	using_history();
}

char *read_command(t_state *state)
{
	char *s;

	s = readline(get_prompt(state));
	if (s == NULL) {
		state->exiting = EXITING;
		return NULL;
	}

	add_history(s);
	return s;
}

static char *get_prompt(t_state *state)
{
	t_value *v;

	if (state == NULL)
	{
		return g_default_prompt;
	}

	v = get_value(state->environ, g_prompt_key);
	if (v == NULL || v->value == NULL)
	{
		return g_default_prompt;
	}

	return v->value;
}
