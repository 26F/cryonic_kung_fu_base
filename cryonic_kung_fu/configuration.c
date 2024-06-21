
#include "configuration.h"
#include "state.h"

#include <assert.h>
#include <SDL2/SDL.h>

void mutate(configuration_t* configuration)
{

	configuration->health = 100;
	configuration->state_p->tick_count += 0.025;

	if (configuration->state_p->keyboard_state[SDL_SCANCODE_ESCAPE])
	{

		configuration->state_p->alive = false;

	}

	if (configuration->state_p->keyboard_state[SDL_SCANCODE_SPACE])
	{

		configuration->is_shooting = true;
		configuration->last_shot_t++;

		// Would be properly "fire rate" and a member
		// of a struct for some game object
		configuration->last_shot_t %= 15;

	} else {

		configuration->is_shooting = false;
		configuration->last_shot_t = 0;

	}

	if (configuration->state_p->keyboard_state[SDL_SCANCODE_RIGHT])
	{

		configuration->music_change = true;

	}

}
