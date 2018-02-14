
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/wait.h>

#include "interpreter.h"

static char *copystr(char *src);

static int exec_cmd(char *path, char *argv[], char *envp[])
{
	pid_t pid;
	int ret;

	pid = fork();
	if (pid != 0)
	{
		int status;
		pid = waitpid(pid, &status, 0);
		if (pid <= 0)
		{
			printf("abnormal error\n");
			return -1;
		}
		if (WIFEXITED(status))
		{
			return WEXITSTATUS(status);
		}
		if (WIFSIGNALED(status))
		{
			printf("received signal: %d\n", WTERMSIG(status));
			return 254;
		}
	}

	ret = execve(path, argv, envp);

	if (ret == -1)
	{
		perror(path);
	} else {
		printf("something went wrong when executing the command\n");
	}
	exit(1);
}

static char *get_cmd_path(t_state *state, t_node *cmd)
{
	return search_path(state->path, cmd->data);
}

static char *evaluate_arg(t_node *arg)
{
	switch (arg->type) {
		case node_type_literal_string:
			return copystr(arg->data);
		default:
			printf("unhandled type %d\n", arg->type);
			return NULL;
	}

	return NULL;
}

static char **get_cmd_args(char *path, t_node *args)
{
	int count;
	int i;
	char **argv;

	count = count_nodes(args);
	argv = calloc(count+2, sizeof(char*));
	if (argv == NULL)
	{
		return NULL;
	}
	argv[0] = copystr(path);
	i = 1;
	while (args != NULL)
	{
		argv[i] = evaluate_arg(args);
		if (argv[i] == NULL)
		{
			argv[i] = calloc(1, sizeof(char));
		}
		i++;
		args = args->next;
	}

	return argv;
}

static char *join_env_value(char *key, char *value)
{
	char *s;
	int key_len, value_len;

	key_len = strlen(key);
	value_len = strlen(value);
	s = calloc(key_len+value_len+2, sizeof(*s));
	if (s == NULL)
	{
		return NULL;
	}
	if (strncpy(s, key, key_len) == NULL)
	{
		free(s);
		return NULL;
	}
	s[key_len] = '=';
	if (strncat(s, value, value_len) == NULL)
	{
		free(s);
		return NULL;
	}

	return s;
}
static char **get_cmd_env(t_state *state)
{
	t_value *value;
	char **env;
	int count;
	int i;

	count = count_values(state->environ);
	env = calloc(count+1, sizeof(*env));
	if (env == NULL)
	{
		return NULL;
	}

	value = state->environ;
	i = 0;
	while (value != NULL)
	{
		env[i] = join_env_value(value->name, value->value);
		if (env[i] != NULL)
		{
			i++;
		}
		value = value->next;
	}
	/*
	 * - populate
	 */
	return env;
}

static void free_values(char **values)
{
	int i;

	if (values == NULL)
	{
		return;
	}
	i = 0;
	while (values[i] != NULL)
	{
		free(values[i]);
		i++;
	}
	free(values);
}

static int execute_command(t_state *state, t_node *cmd)
{
	char *path;
	char **args;
	char **env;
	int ret;

	path = get_cmd_path(state, cmd);
	if (path == NULL)
	{
		printf("%s: Command not found\n", cmd->data);
		return 1;
	}

	args = get_cmd_args(path, cmd->children);
	if (args == NULL)
	{
		free(path);
		return -1;
	}

	env = get_cmd_env(state);
	if (env == NULL)
	{
		free_values(args);
		free(path);
		return -1;
	}

	ret = exec_cmd(path, args, env);

	free_values(args);
	free_values(env);
	free(path);
	return ret;
}

static int execute_statement(t_state *state, t_node *stmt)
{
	switch (stmt->type) {
		case node_type_command:
			return execute_command(state, stmt);
		default:
			printf("cannot execute statement of type %d\n", stmt->type);
			return -1;
	}
}

int interpret(t_state *state, t_node *ast)
{
	int ret;

	while (ast != NULL) {
		ret = execute_statement(state, ast);
		if (ret == -1)
		{
			return ret;
		}
		state->last_exit_code = ret;
		ast = ast->next;
	}

	return 0;
}

static char *copystr(char *src)
{
	char *dst;
	int len;

	if (src == NULL)
	{
		return NULL;
	}
	len = strlen(src);
	dst = calloc(len+1, sizeof(*dst));
	if (dst == NULL)
	{
		return NULL;
	}

	return strncpy(dst, src, len);
}
