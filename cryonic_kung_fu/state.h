
/*
Users of cryonic_kung_fu add to the state_t the intended keys which their interactive application uses.

*/

#ifndef STATE_H
#define STATE_H

#include <SDL2/SDL.h>
#include <stdbool.h>

typedef struct 
{


	float tick_count;

	bool alive;
	
	int mouse_x;
	int mouse_y;

	float lmbtn;
	float mmbtn;
	float rmbtn;
	
	const Uint8* keyboard_state;
	
	Uint32 mouse_state;

	bool w;
	bool a;
	bool s;
	bool d;

} state_t;


state_t reset_state(void);
void update_state(state_t* state);

#endif // STATE_H