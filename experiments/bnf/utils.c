
#include <stdlib.h>
#include <string.h>

char *copystr(char *src)
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

char *copysubstr(char *src, int start, int end)
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

