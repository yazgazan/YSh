
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "states.h"

static char *copystr(char *src);
static char *copysubstr(char *src, int start, int end);

static int dir_exists(char *path)
{
	struct stat infos;

	if (stat(path, &infos) != 0)
	{
		return 0;
	}
	if (infos.st_mode & S_IFDIR)
	{
		return 1;
	}
	/* TODO(yazgazan): check permissions */

	return 0;
}

static int count_colons(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == ':')
		{
			count++;
		}
		i++;
	}

	return count;
}

static char **split_path(char *path)
{
	char **paths;
	int count, i, j, start;

	count = count_colons(path) + 1;
	paths = calloc(count, sizeof(*paths));
	if (paths == NULL)
	{
		return NULL;
	}

	start = 0;
	i = 0;
	j = 0;
	while (path[i] != '\0')
	{
		if (path[i] == ':')
		{
			paths[j] = copysubstr(path, start, i);
			if (paths[j] == NULL)
			{
				start = i+1;
				continue;
			}
			start = i+1;
			j++;
		}
		i++;
	}

	return paths;
}

void init_path_from_env(t_state *state)
{
	t_value *envpath;
	char **paths;
	int i;

	envpath = get_value(state->environ, "PATH");
	if (envpath == NULL)
	{
		return;
	}
	paths = split_path(envpath->value);
	if (paths == NULL)
	{
		return;
	}
	i = 0;
	while (paths[i] != NULL)
	{
		if (!dir_exists(paths[i]))
		{
			i++;
			continue;
		}
		if (set_value(state->path, paths[i], paths[i]) != NULL)
		{
			i++;
			continue;
		}
		state->path = create_value(state->path, paths[i], paths[i]);
		if (state->path == NULL)
		{
			break;
		}
		i++;
	}
	i = 0;
	while (paths[i] != NULL)
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

static char *join_path(char *path, char *name)
{
	char *s;
	int path_len, name_len;

	path_len = strlen(path);
	name_len = strlen(name);
	s = calloc(path_len+name_len+2, sizeof(*s));
	if (s == NULL)
	{
		return NULL;
	}
	if (strncpy(s, path, path_len) == NULL)
	{
		free(s);
		return NULL;
	}
	s[path_len] = '/';
	if (strncat(s, name, name_len) == NULL)
	{
		free(s);
		return NULL;
	}

	return s;
}

static int is_absolute(char *path)
{
	if (path[0] == '/')
	{
		return 1;
	}

	return 0;
}

static int is_relative(char *path)
{
	if (path[0] == '.')
	{
		return 1;
	}

	return 0;
}


static char *search_dir(char *path, char *name)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir(path);
	if (dir == NULL)
	{
		return NULL;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, name) == 0)
		{
			closedir(dir);
			return join_path(path, name);
		}
	}
	closedir(dir);

	return NULL;
}

char *search_path(t_value *path, char *name)
{
	char *fpath;

	if (is_absolute(name) || is_relative(name))
	{
		return copystr(name);
	}

	while (path != NULL)
	{
		fpath = search_dir(path->value, name);
		if (fpath != NULL)
		{
			return fpath;
		}
		path = path->next;
	}

	return NULL;
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

static char *copysubstr(char *src, int start, int end)
{
	char *dst;
	int len;

	if (start >= end)
	{
		return NULL;
	}
	len = end - start;

	dst = calloc(len+1, sizeof(*dst));
	if (dst == NULL)
	{
		return NULL;
	}

	dst = strncpy(dst, src + start, len);
	dst[len] = '\0';

	return dst;
}

