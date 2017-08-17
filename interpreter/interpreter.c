
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

	(void)path;
	(void)argv;
	(void)envp;

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

	execve(path, argv, envp);

	printf("something went wrong when executing the command\n");
	exit(1);
}

static char *get_cmd_path(t_node *cmd)
{
	return cmd->data;
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

static char **get_cmd_env(t_state *state)
{
	(void)state;

	return calloc(1, sizeof(char*));
}

static int execute_command(t_state *state, t_node *cmd)
{
	char *path;
	char **args;
	char **env;

	path = get_cmd_path(cmd);
	if (path == NULL)
	{
		/* TODO(yazgazan): error handling */
		return 1;
	}

	args = get_cmd_args(path, cmd->children);
	if (args == NULL)
	{
		/* TODO(yazgazan): error handling */
		return 1;
	}

	env = get_cmd_env(state);
	if (args == NULL)
	{
		/* TODO(yazgazan): error handling */
		return 1;
	}

	return exec_cmd(path, args, env);
}

static int execute_statement(t_state *state, t_node *stmt)
{
	switch (stmt->type) {
		case node_type_command:
			return execute_command(state, stmt);
		default:
			printf("cannot execute statement of type %d\n", stmt->type);
			return 1;
	}
}

int interpret(t_state *state, t_node *ast)
{
	int ret;

	while (ast != NULL) {
		ret = execute_statement(state, ast);
		if (ret != 0)
		{
			return ret;
		}
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
