
#include <stdio.h>
#include "libsinternal.h"
#include "configuration.h"
#include "test.h"
#include "ascii_display_dbg.h"
#include "sound.h"


/*

In this file we set up the game's initial state 
and then have a simple game loop which passes the 
game's configuration or any of its members as a pointer to various 
stages of the logic:

update_state polls and sets the desired keyboard and mouse button states for use
in your program.

debug_print lets you view the configuration of the entire application, as this is 
by design to reduce coupling problems. The sdl internals are de-coupled from the application
configuration - a least I tried. 

we mutate the configuration of the application as a function of your desired logic.

we pass the configuration to the play_audio and then the draw_frame functions

*/

int main(void)
{

	// Init SDL2 internals
	sdl_t sdlh = init();

	// create drawing plane vertices
	vabo_t vabo = verts();

	// build shaders
	shaderProgram_t shaderprg = buildShaders();

	// get shader uniforms into a struct
	uniforms_t unfrms = get_uniforms(&shaderprg);

	// get keyboard and mouse state
	state_t state = reset_state();


	// configuration of game everything and is an adjunct to the controller etc keyboard / mouse
	configuration_t configuration;
	configuration.health = 100;
	configuration.sdl_p      = &sdlh;
    configuration.vabo_p     = &vabo; 
    configuration.shader_p   = &shaderprg; 
    configuration.uniforms_p = &unfrms;
    configuration.state_p    = &state;

    // When changing music
    configuration.music_change = false;

    configuration.is_shooting = false;
    configuration.last_shot_t = 0;

    sdl_state_t sdl_state;
    sdl_state.state = &state;
    sdl_state.uniforms_p = &unfrms;
    sdl_state.shader_p = &shaderprg;
    sdl_state.vabo_p = & vabo;
    sdl_state.sdl_p = &sdlh;
    sdl_state.ticks = &state.tick_count;

    play_music(sdlh.menu_music.track, &sdlh.menu_music.is_playing);

	while (state.alive)
	{

		// keyboard and mouse state
		update_state(&state);

		// test configuration before or after mutation
#ifdef DEBUG_YES_H
		debug_print(sdlh.renderer, &configuration);
#endif
		// update the game configuration, including uniforms
		mutate(&configuration);

		handle_audio(&configuration, &sdlh);

		draw_frame(&sdl_state);

		SDL_RenderPresent(sdlh.renderer);
		SDL_Delay(0.016);


	}

	sdlDestroyDelete(&sdl_state);
	return 0;

}