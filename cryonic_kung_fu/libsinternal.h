
#ifndef LIBS_INTERNAL_H
#define LIBS_INTERNAL_H

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdbool.h>
#include <assert.h>
#include "state.h"

extern float drawing_plane_verts[4][2];


// Each sound should have a distinct channel
// to ensure smooth playing
typedef struct 
{

	Mix_Chunk* sfx;
	int channel_id;

} sfx_t;


typedef struct
{


	Mix_Music* track;
	bool is_playing;
	
} music_t;


typedef struct 
{	

	GLuint iResolution;
	GLuint iTime;
	GLuint iMouse;
	GLuint iKeyboard;

} uniforms_t;


typedef struct
{


	GLuint vert;
	GLuint frag;
	GLuint program;

} shaderProgram_t;




typedef struct 
{


	GLuint a_id;
	GLuint o_id;

	
} vabo_t;


typedef struct 
{
	

	SDL_DisplayMode display_mode;
	SDL_Window* SDL_window_ptr;
	SDL_Renderer* renderer;
	SDL_GLContext gl_context;
	
	// Music goes here
	music_t menu_music;
	music_t boss_battle;

	// SFX go here
	sfx_t gun_sfx1;


} sdl_t;




typedef struct
{

	state_t* state;
	uniforms_t* uniforms_p;
	shaderProgram_t* shader_p;
	vabo_t* vabo_p;
	sdl_t* sdl_p;
	float* ticks;

} sdl_state_t;


sdl_t init(void);
vabo_t verts(void);
void display_debug_text(SDL_Texture* texture, SDL_Renderer* renderer, int text_w, int text_h);
uniforms_t get_uniforms(shaderProgram_t* shaderprg);
shaderProgram_t buildShaders(void);
void draw_frame(sdl_state_t* display);
void swap_buffer_delay(SDL_Window* sdl_window_ptr);
void sdlDestroyDelete(sdl_state_t* display);

#endif // LIBS_INTERNAL_H
