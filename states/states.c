
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "states.h"

t_scope *new_scope(char *id);
char *copystr(char *src);
t_value *new_value(char *id, char *value);

char g_global_scope[] = "g";

t_state *new_state(void)
{
	t_state *state;

	state = malloc(sizeof(*state));
	if (state == NULL)
	{
		return NULL;
	}

	state->environ = NULL;
	state->variables = create_scope(NULL, g_global_scope);
	state->last_exit_code = 0;

	return state;
}

void delete_state(t_state *state)
{
	delete_scopes(state->variables);
	delete_values(state->environ);
	free(state);
}

t_scope *create_scope(t_scope *scopes, char *id)
{
	t_scope *cur;

	if (scopes == NULL)
	{
		return new_scope(id);
	}

	cur = scopes;
	while (cur->next != NULL)
	{
		if (strcmp(id, cur->id) == 0)
		{
			return NULL;
		}
		cur = cur->next;
	}

	cur->next = new_scope(id);

	return cur;
}

void delete_scopes(t_scope *scopes)
{
	if (scopes == NULL)
	{
		return;
	}

	delete_scopes(scopes->next);
	free(scopes->id);
	delete_values(scopes->variables);
	free(scopes);

	return;
}

t_scope *new_scope(char *id)
{
	t_scope *scope;
	char *id_cpy;

	id_cpy = copystr(id);
	if (id_cpy == NULL)
	{
		return NULL;
	}

	scope = malloc(sizeof(*scope));
	if (scope == NULL)
	{
		free(id_cpy);
		return NULL;
	}

	scope->id = id_cpy;
	scope->variables = NULL;
	scope->next = NULL;

	return scope;
}

char *copystr(char *src)
{
	char *dst;
	size_t len;

	if (src == NULL)
	{
		return NULL;
	}
	len = strlen(src);
	dst = malloc(sizeof(*dst) * len + 1);

	return strncpy(dst, src, len);
}

t_value *create_value(t_value *values, char *name, char *value)
{
	t_value *cur;

	if (values == NULL)
	{
		return new_value(name, value);
	}

	cur = values;
	while (cur->next != NULL)
	{
		if (strcmp(name, cur->name) == 0)
		{
			return NULL;
		}
		cur = cur->next;
	}

	cur->next = new_value(name, value);

	return cur;
}

t_value *get_value(t_value *values, char *name)
{
	if (name == NULL)
	{
		return NULL;
	}

	while (values != NULL)
	{
		if (strcmp(name, values->name) == 0)
		{
			return values;
		}
		values = values->next;
	}

	return NULL;
}

t_value *set_value(t_value *values, char *name, char *value)
{
	char *val;
	if (name == NULL)
	{
		return NULL;
	}

	while (values != NULL)
	{
		if (strcmp(name, values->name) == 0)
		{
			val = copystr(value);
			if (val == NULL)
			{
				return NULL;
			}
			free(values->value);
			values->value = val;
			return values;
		}
		values = values->next;
	}

	return NULL;
}

void delete_values(t_value *values)
{
	if (values == NULL)
	{
		return;
	}

	delete_values(values->next);
	free(values->name);
	free(values->value);
	free(values);

	return;
}

t_value *new_value(char *id, char *value)
{
	t_value *val;
	char *id_cpy;
	char *val_cpy;

	id_cpy = copystr(id);
	if (id_cpy == NULL)
	{
		return NULL;
	}
	val_cpy = copystr(value);
	if (val_cpy == NULL)
	{
		free(id_cpy);
		return NULL;
	}

	val = malloc(sizeof(*val));
	if (val == NULL)
	{
		free(id_cpy);
		free(val_cpy);
		return NULL;
	}

	val->name = id_cpy;
	val->value = val_cpy;
	val->next = NULL;

	return val;
}

t_scope *get_scope(t_scope *scopes, char *id)
{
	if (id == NULL)
	{
		return NULL;
	}

	while (scopes != NULL)
	{
		if (strcmp(id, scopes->id) == 0)
		{
			return scopes;
		}
		scopes = scopes->next;
	}

	return NULL;
}

void print_scopes(t_scope *scopes)
{
	if (scopes == NULL)
	{
		return;
	}
	while (scopes != NULL)
	{
		printf("[%s]\n", scopes->id);
		printf("\n");
		scopes = scopes->next;
	}
}

void print_values(t_value *values)
{
	if (values == NULL)
	{
		return;
	}
	while (values != NULL)
	{
		printf("%s=%s\n", values->name, values->value);
		values = values->next;
	}
}

void print_state(t_state *state)
{
	if (state == NULL)
	{
		return;
	}

	printf("== Environment ==\n");
	print_values(state->environ);
	printf("\n== Scopes ==\n");
	print_scopes(state->variables);
}