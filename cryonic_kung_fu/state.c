
#include "state.h"
#include <stdint.h>

/*

Anything added to the state_t must have its initial value set and this is used for reset as well.
cryonic_kung_fu users handle the keyboard and mouse events here.

*/


// Reset and initial state here
state_t reset_state(void)
{

	// add buttons used and update / reset flags for them

	state_t state;
	state.tick_count = 0.0;

	state.alive = true;
	
	state.mouse_x = 0;
	state.mouse_y = 0;

	state.lmbtn = 0.0;
	state.mmbtn = 0.0;
	state.rmbtn = 0.0;

	state.keyboard_state = SDL_GetKeyboardState(NULL);
	state.mouse_state = SDL_GetMouseState(&state.mouse_x, &state.mouse_y);

	state.w = false;
	state.a = false;
	state.s = false;
	state.d = false;

	return state;

}


// The logic for mouse and keyboard events is done here
void update_state(state_t* state)
{

	SDL_PumpEvents();
	state->mouse_state = SDL_GetMouseState(&state->mouse_x, &state->mouse_y);
	state->keyboard_state = SDL_GetKeyboardState(NULL);

	if (SDL_BUTTON(SDL_BUTTON_LEFT) & state->mouse_state)
	{

		state->lmbtn = 1.0;

	} else {

		state->lmbtn = -1.0;

	}

	if (SDL_BUTTON(SDL_BUTTON_MIDDLE) & state->mouse_state)
	{

		state->mmbtn = 1.0;

	} else {

		state->mmbtn = -1.0;

	}

	if (SDL_BUTTON(SDL_BUTTON_RIGHT) & state->mouse_state)
	{

		state->rmbtn = 1.0;

	} else {

		state->rmbtn = -1.0;

	}


	state->w = false;
	state->a = false;
	state->s = false;
	state->d = false;

	if (state->keyboard_state[SDL_SCANCODE_W])
	{


		state->w = true;

	}

	if (state->keyboard_state[SDL_SCANCODE_A])
	{


		state->a = true;

	}

	if (state->keyboard_state[SDL_SCANCODE_S])
	{

		state->s = true;

	}

	if (state->keyboard_state[SDL_SCANCODE_D])
	{


		state->d = true;

	}


}




