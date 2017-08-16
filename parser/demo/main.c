
#include <stdio.h>

#include "../lexer.h"
#include "../parser.h"

int main()
{
	char *s = " hello \n\tworld  !\r\n haha";
	t_token *tokens;
	t_node *ast;

	tokens = lex(s);
	if (tokens == NULL)
	{
		printf("lexer failed.\n");
		return 1;
	}

	printf("tokens:\n");
	print_token(tokens);

	ast = parse(tokens);
	if (ast == NULL)
	{
		printf("parser failed.\n");
		return 1;
	}

	printf("\nast:\n");
	print_node(ast);
	return 0;
}

