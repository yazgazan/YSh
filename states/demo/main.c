
#include <stdlib.h>

#include "../states.h"

int main(void)
{
	t_state *state;

	state = new_state();

	delete_state(state);
	return 0;
}

