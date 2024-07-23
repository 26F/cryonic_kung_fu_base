
#include "libsinternal.h"
#include "state.h"
#include "loadshader.h"
#include <assert.h>


float drawing_plane_verts[4][2] = 
{
	{-1.0, -1.0},
	{1.0,  -1.0},
	{1.0,   1.0},
	{-1.0,  1.0},
};

sdl_t init(void)
{

	assert(SDL_Init(SDL_INIT_VIDEO) == 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 4);

	sdl_t sdl;
	
	assert(SDL_GetDesktopDisplayMode(0, &sdl.display_mode) == 0);
	sdl.SDL_window_ptr = SDL_CreateWindow("cryonic_kung_fu",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		sdl.display_mode.w,
		sdl.display_mode.h,
		SDL_WINDOW_OPENGL);

	assert(sdl.SDL_window_ptr);

	SDL_SetWindowFullscreen(sdl.SDL_window_ptr, SDL_WINDOW_FULLSCREEN_DESKTOP);

	sdl.gl_context = SDL_GL_CreateContext(sdl.SDL_window_ptr);
	assert(sdl.gl_context);
	assert(glewInit() == GLEW_OK);

	sdl.renderer = SDL_CreateRenderer(sdl.SDL_window_ptr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(sdl.renderer);

	// Sound effects and music are set here
	//assert(Mix_OpenAudio(48000, MIX_DEFAULT_FORMAT, 2, 2048) == 0);

	// An example of loading boss battle music for a game or difficult to use application.
	//sdl.menu_music.track = Mix_LoadMUS("./music/menu.wav");
	//sdl.menu_music.is_playing = false;
	//assert(sdl.menu_music.track);

	//sdl.boss_battle.track = Mix_LoadMUS("./music/boss_battle.wav");
	//sdl.boss_battle.is_playing = false;
	//assert(sdl.boss_battle.track);

	// Example of loading a sound effect for use in a game or interactive application
	//sdl.gun_sfx1.sfx = Mix_LoadWAV("./sfx/shot_sfx.wav");
	//sdl.gun_sfx1.channel_id = 0;	
	//assert(sdl.gun_sfx1.sfx);

	SDL_ShowCursor(0);

	return sdl;

}



vabo_t verts(void)
{

	vabo_t vabo;
	glGenVertexArrays(1, &vabo.a_id);
	glBindVertexArray(vabo.a_id);

	glGenBuffers(1, &vabo.o_id);
	glBindBuffer(GL_ARRAY_BUFFER, vabo.o_id);
	glBufferData(GL_ARRAY_BUFFER, sizeof(drawing_plane_verts), drawing_plane_verts, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

	glBindVertexArray(0);

	return vabo;
}



shaderProgram_t buildShaders(void)
{


	const char* vertSrc = shader("./shaders/vertex_shader.frag");
	const char* fragSrc = shader("./shaders/fragment_shader.frag");

	shaderProgram_t program;
	program.vert = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(program.vert, 1, &vertSrc, NULL);
	glCompileShader(program.vert);

	program.frag = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(program.frag, 1, &fragSrc, NULL);
	glCompileShader(program.frag);

	program.program = glCreateProgram();
	glAttachShader(program.program, program.vert);
	glAttachShader(program.program, program.frag);
	glLinkProgram(program.program);

	GLint compilationStatus = 0;
	GLchar infoLog[512];

	glGetShaderiv(program.vert, GL_COMPILE_STATUS, &compilationStatus);

	if (!(compilationStatus))
	{

		glGetShaderInfoLog(program.vert, 512, NULL, infoLog);
		printf("%s\n", infoLog);

	}

	glGetShaderiv(program.frag, GL_COMPILE_STATUS, &compilationStatus);

	if (!(compilationStatus))
	{

		glGetShaderInfoLog(program.frag, 512, NULL, infoLog);
		printf("%s\n", infoLog);

	}

	glDeleteShader(program.vert);
	glDeleteShader(program.frag);
	free((char*)vertSrc);
	free((char*)fragSrc);

	return program;

}


uniforms_t get_uniforms(shaderProgram_t* shaderprg)
{


	assert(shaderprg);
	uniforms_t unfms;
	unfms.iResolution = glGetUniformLocation(shaderprg->program, "iResolution");
	unfms.iTime       = glGetUniformLocation(shaderprg->program, "iTime");
	unfms.iMouse      = glGetUniformLocation(shaderprg->program, "iMouse");
	unfms.iKeyboard   = glGetUniformLocation(shaderprg->program, "iKeyboard");

	return unfms;


}



void draw_frame(sdl_state_t* display)
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glUseProgram(display->shader_p->program);

	glUniform2f(display->uniforms_p->iResolution, (float)(display->sdl_p->display_mode.w), (float)(display->sdl_p->display_mode.h));
	
	glUniform1f(display->uniforms_p->iTime, *display->ticks);

	glUniform4f(display->uniforms_p->iMouse, (float)(display->state->mouse_x), (float)(display->state->mouse_y), (float)(display->state->lmbtn), (float)(display->state->rmbtn));
	
	glUniform1i(display->uniforms_p->iKeyboard, 0);

	glBindVertexArray(display->vabo_p->a_id);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

	glBindVertexArray(0);
	glUseProgram(0);
}




/*
Everything that gets allocated must be destroyed
*/
void sdlDestroyDelete(sdl_state_t* sdl_state)
{

	// free music
	//Mix_FreeMusic(sdl_state->sdl_p->menu_music.track);
	//Mix_FreeMusic(sdl_state->sdl_p->boss_battle.track);

    // free sound effects
	//Mix_FreeChunk(sdl_state->sdl_p->gun_sfx1.sfx);

	// Close audio context
	//Mix_CloseAudio();

	glDeleteVertexArrays(1, &sdl_state->vabo_p->a_id);
	glDeleteBuffers(1, &sdl_state->vabo_p->o_id);
	SDL_GL_DeleteContext(sdl_state->sdl_p->gl_context);
	SDL_DestroyWindow(sdl_state->sdl_p->SDL_window_ptr);
	SDL_Quit();
}