
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "ast.h"

static char *copystr(char *src);

t_node *new_node(e_node_type type, char *data)
{
	t_node *node;

	node = calloc(1, sizeof(*node));
	if (node == NULL)
	{
		return NULL;
	}

	node->type = type;
	node->data = copystr(data);
	if (node->data == NULL)
	{
		free(node);
		return NULL;
	}

	node->context.raw_pos = 0;
	node->context.excerpt_pos = 0;
	node->context.excerpt = NULL;
	node->next = NULL;

	return node;
}

void delete_node(t_node *node)
{
	if (node->next != NULL)
	{
		delete_node(node->next);
	}
	if (node->children != NULL)
	{
		delete_node(node->children);
	}
	if (node->context.excerpt != NULL)
	{
		free(node->context.excerpt);
	}
	if (node->data != NULL)
	{
		free(node->data);
	}
	free(node);

	return;
}

t_node *add_node(t_node *root, t_node *node)
{
	t_node *cur;

	if (root == NULL)
	{
		return node;
	}
	cur = root;
	while (cur->next != NULL)
	{
		cur = cur->next;
	}
	cur->next = node;

	return root;
}

void print_node(t_node *node)
{
	switch (node->type)
	{
		case node_type_command:
			printf("<command '%s'>(", node->data);
			if (node->children != NULL)
			{
				print_node(node->children);
			}
			printf(")\n");
			break;
		case node_type_literal_string:
			printf("<lit '%s'>", node->data);
			break;
		default:
			printf("<unknown '%s'>", node->data);
	}

	if (node->next != NULL)
	{
		printf(" ");
		print_node(node->next);
	}
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
