
#include <stdio.h>
#include <string.h>

#include "../states.h"

#define TEST(x) if(x != 0) { printf("FAIL "#x"\n"); } else { printf("OK   "#x"\n"); }

int state_lifetime_no_crash();

int state_add_scope();
int state_get_scope();
int state_get_undefined_scope();

int state_add_value();
int state_get_value();
int state_get_undefined_value();
int state_set_value();
int exiting_string_test();

int main(void)
{
	printf("Running tests...\n\n");

	TEST(state_lifetime_no_crash());

	TEST(state_add_scope());
	TEST(state_get_scope());
	TEST(state_get_undefined_scope());

	TEST(state_add_value());
	TEST(state_get_value());
	TEST(state_get_undefined_value());
	TEST(state_set_value());
	TEST(exiting_string_test())

	printf("\n");
	return 0;
}

int state_lifetime_no_crash()
{
	t_state *state;

	state = new_state();

	delete_state(state);
	return 0;
}

int state_add_scope()
{
	t_state *state;

	state = new_state();

	state->variables = create_scope(state->variables, "f:bar");

	delete_state(state);
	return 0;
}

int state_get_scope()
{
	t_state *state;
	t_scope *scope;

	state = new_state();

	state->variables = create_scope(state->variables, "f:bar");
	scope = get_scope(state->variables, "f:bar");
	if (scope == NULL)
	{
		return 1;
	}

	delete_state(state);
	return 0;
}

int state_get_undefined_scope()
{
	t_state *state;
	t_scope *scope;

	state = new_state();

	state->variables = create_scope(state->variables, "f:bar");
	scope = get_scope(state->variables, "f:buzz");
	if (scope != NULL)
	{
		return 1;
	}

	delete_state(state);
	return 0;
}


int state_add_value()
{
	t_state *state;

	state = new_state();

	state->environ = create_value(state->environ, "hello", "world");

	delete_state(state);
	return 0;
}

int state_get_value()
{
	t_state *state;
	t_value *value;

	state = new_state();

	state->environ = create_value(state->environ, "hello", "world");
	value = get_value(state->environ, "hello");
	if (value == NULL || strcmp(value->value, "world") != 0)
	{
		return 1;
	}

	delete_state(state);
	return 0;
}

int state_get_undefined_value()
{
	t_state *state;
	t_value *value;

	state = new_state();

	state->environ = create_value(state->environ, "hello", "world");
	value = get_value(state->environ, "foo");
	if (value != NULL)
	{
		return 1;
	}

	delete_state(state);
	return 0;
}

int state_set_value()
{
	t_state *state;
	t_value *value;

	state = new_state();

	state->environ = create_value(state->environ, "hello", "world");
	value = get_value(state->environ, "hello");
	if (value == NULL || strcmp(value->value, "world") != 0)
	{
		return 1;
	}

	value = set_value(state->environ, "hello", "mickey");
	if (value == NULL)
	{
		return 1;
	}

	value = get_value(state->environ, "hello");
	if (value == NULL || strcmp(value->value, "mickey") != 0)
	{
		return 1;
	}

	delete_state(state);
	return 0;
}

int exiting_string_test()
{
	char *s;

	s = exiting_string(NOT_EXITING);
	if (s == NULL || strcmp(s, "not exiting")) {
		return 1;
	}

	s = exiting_string(EXITING);
	if (s == NULL || strcmp(s, "exiting")) {
		return 1;
	}
}
