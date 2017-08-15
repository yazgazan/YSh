
#include <stdlib.h>
#include <stdio.h>

#include "../reader.h"
#include "../../states/states.h"

int main(void)
{
	char *s;
	t_state *state;

	state = new_state();
	if (state == NULL) {
		return 1;
	}
	init_from_env(state);

	while (42) {
		s = read_command(state);
		if (state->exiting == EXITING) {
			printf("exiting...\n");
			return 0;
		}
		printf("read command line: %s\n", s);
	}

	delete_state(state);
	return 0;
}

