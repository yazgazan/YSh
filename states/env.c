
#include <stdlib.h>
#include <string.h>

#include "states.h"

extern char **environ;

static char **split_env(char *env)
{
	int pos, i;
	char **parts;

	pos = -1;
	i = 0;
	while (env[i] != '\0')
	{
		if (env[i] == '=')
		{
			pos = i;
		}
		i++;
	}
	if (pos == -1)
	{
		return NULL;
	}

	parts = calloc(2, sizeof(*parts));
	if (parts == NULL)
	{
		return NULL;
	}

	parts[0] = calloc(pos+1, sizeof(**parts));
	if (parts[0] == NULL)
	{
		free(parts);
		return NULL;
	}
	parts[0][pos] = '\0';
	parts[1] = calloc(i-pos, sizeof(**parts));
	if (parts[1] == NULL)
	{
		free(parts[0]);
		free(parts);
		return NULL;
	}
	parts[1][(i-pos)-1] = '\0';

	strncpy(parts[0], env, pos);
	strncpy(parts[1], env+pos+1, (i - pos) - 1);
	return parts;
}

void init_from_env(t_state *state)
{
	char **parts;
	int i;

	if (environ == NULL)
	{
		return;
	}
	i = 0;
	while (environ[i] != NULL)
	{
		parts = split_env(environ[i]);
		if (parts == NULL)
		{
			i++;
			continue;
		}
		state->environ = create_value(state->environ, parts[0], parts[1]);
		free(parts[0]);
		free(parts[1]);
		free(parts);
		if (state->environ == NULL)
		{
			/* TODO(yazgazan): error handling */
			return;
		}
		i++;
	}

	init_path_from_env(state);
}

