
#ifndef _CONTEXT_H_
#define _CONTEXT_H_

typedef struct {
	int line;
	int col;
	int excerpt_pos;
	char *excerpt;
} t_context;

#endif
