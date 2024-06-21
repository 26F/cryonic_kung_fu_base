
#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "libsinternal.h"

// acts like an adjunct updating the game variables 
// with regards the keyboard and mouse state.
typedef struct
{


	sdl_t* sdl_p;
	vabo_t* vabo_p;
	shaderProgram_t* shader_p;
	uniforms_t* uniforms_p;
	state_t* state_p;

	// you are encoraged to actually put structs here... for you game objects
	// add game vars and shit here
	int health;

	// example of logic for if player is shooting. Better to put
	// this type of stuff in a struct. 
	bool is_shooting;
	int last_shot_t;

	bool music_change;

} configuration_t;

void mutate(configuration_t* configuration);

#endif // CONFIGURATION_H