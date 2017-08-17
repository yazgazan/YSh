
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static t_token *read_literal(t_token **tokens)
{
	t_token *token;

	if (tokens == NULL || *tokens == NULL)
	{
		return NULL;
	}
	if ((*tokens)->type != token_type_literal)
	{
		return NULL;
	}
	token = *tokens;

	*tokens = token->next;
	return token;
}

static t_node *read_literal_node(t_token **tokens)
{
	t_token *root;
	t_token *lit_id;
	t_node *lit;

	root = *tokens;
	lit_id = read_literal(tokens);
	if (lit_id == NULL)
	{
		return NULL;
	}
	/* TODO(yazgazan): handle more types */
	lit = new_node(node_type_literal_string, lit_id->data);
	if (lit == NULL)
	{
		*tokens = root;
		return NULL;
	}

	lit->context.raw_pos = lit_id->context.raw_pos;

	return lit;
}

static t_node *read_args(t_token **tokens)
{
	t_node *args;

	args = read_literal_node(tokens);
	if (args == NULL)
	{
		return NULL;
	}

	args->next = read_args(tokens);

	return args;
}

static t_node *read_command(t_token **tokens)
{
	t_token *root;
	t_token *cmd_id;
	t_node *cmd;

	root = *tokens;

	cmd_id = read_literal(tokens);
	if (cmd_id == NULL)
	{
		return NULL;
	}
	cmd = new_node(node_type_command, cmd_id->data);
	if (cmd == NULL)
	{
		*tokens = root;
		return NULL;
	}
	cmd->context.raw_pos = cmd_id->context.raw_pos;
	cmd->context.excerpt_pos = cmd_id->context.excerpt_pos;
	cmd->context.excerpt = cmd_id->context.excerpt;

	cmd->children = read_args(tokens);

	return cmd;
}

t_node *parse(t_token *tokens)
{
	return read_command(&tokens);
}
