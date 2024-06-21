
#include "ascii_display_dbg.h"
#include "test.h"
#include "configuration.h"
#include <SDL2/SDL.h>

/*

In this file cryonic_kung_fu users are advised to do the debugging of their application.
Calling: debug_print(sdlh.renderer, &configuration) in main.c can be done before or after 
mutating the configuration of the application state by calling: mutate(&configuration)
in main.c
*/

// cryonic_kung_fu may want to create their own font using
// the ascii_font_maker.py located in the tools folder,
// but this is generally a long and boring process.
const int ASCII_FONT_DATA[ASCII_CHAR_NM][ASCII_CHAR_WH] = 
{
		{8, 8, 8, 8, 0, 0, 8, 0},
		{40, 40, 40, 0, 0, 0, 0, 0},
		{20, 20, 126, 20, 40, 126, 40, 40},
		{16, 60, 54, 50, 24, 92, 124, 56},
		{0, 98, 100, 8, 16, 38, 70, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 64, 64, 64, 0, 0, 0, 0},
		{32, 64, 64, 64, 64, 64, 96, 32},
		{8, 12, 4, 4, 4, 4, 12, 8},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 32, 48, 48, 96},
		{0, 0, 0, 0, 124, 0, 0, 0},
		{0, 0, 0, 0, 16, 112, 96, 0},
		{0, 2, 6, 12, 24, 48, 96, 0},
		{24, 60, 110, 102, 102, 118, 60, 24},
		{0, 120, 24, 24, 24, 24, 24, 124},
		{56, 76, 76, 12, 24, 48, 96, 126},
		{60, 36, 12, 24, 12, 4, 108, 56},
		{56, 104, 200, 136, 254, 252, 8, 8},
		{126, 96, 96, 120, 4, 2, 4, 124},
		{60, 36, 64, 92, 102, 66, 100, 60},
		{62, 62, 2, 4, 4, 8, 24, 16},
		{28, 38, 50, 28, 38, 34, 50, 28},
		{60, 38, 66, 102, 58, 2, 36, 60},
		{0, 96, 0, 0, 0, 0, 96, 0},
		{96, 96, 0, 0, 0, 32, 32, 96},
		{0, 0, 12, 48, 64, 48, 12, 0},
		{0, 0, 126, 0, 0, 126, 0, 0},
		{0, 48, 12, 2, 12, 48, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{0, 0, 0, 0, 0, 0, 0, 0},
		{24, 24, 24, 40, 60, 124, 76, 76},
		{60, 60, 40, 44, 36, 36, 120, 48},
		{28, 50, 96, 64, 64, 96, 98, 60},
		{56, 38, 34, 34, 66, 68, 76, 112},
		{28, 48, 32, 32, 60, 32, 56, 4},
		{60, 32, 32, 32, 60, 32, 32, 32},
		{56, 68, 128, 134, 138, 130, 68, 56},
		{0, 36, 36, 60, 36, 36, 36, 64},
		{30, 28, 40, 8, 8, 8, 28, 48},
		{62, 12, 12, 12, 12, 12, 24, 0},
		{33, 34, 36, 36, 40, 56, 36, 35},
		{0, 32, 32, 32, 32, 32, 60, 0},
		{0, 0, 195, 165, 153, 129, 129, 0},
		{2, 2, 98, 82, 82, 74, 74, 70},
		{0, 24, 62, 98, 198, 220, 112, 0},
		{124, 70, 66, 70, 124, 64, 64, 64},
		{16, 56, 70, 195, 130, 190, 156, 126},
		{31, 127, 118, 28, 56, 48, 62, 33},
		{126, 98, 50, 24, 12, 4, 76, 120},
		{0, 126, 8, 8, 24, 16, 16, 0},
		{0, 51, 34, 34, 34, 34, 60, 0},
		{0, 0, 0, 68, 68, 72, 40, 16},
		{64, 65, 65, 75, 94, 126, 36, 0},
		{0, 116, 200, 24, 24, 154, 238, 0},
		{76, 156, 228, 204, 8, 8, 24, 16},
		{62, 126, 12, 24, 48, 32, 126, 30},
		{96, 64, 64, 64, 64, 64, 64, 112},
		{0, 64, 32, 48, 16, 8, 12, 4},
		{14, 6, 2, 2, 2, 2, 2, 6},
		{16, 56, 44, 100, 64, 0, 0, 0},
};

// NULL terminated string ready for use for debug printing stuff
char __debug_string[DEBUG_STRING_LN] = {0};


// meant to be called by __dbg_print not by you.
void draw_char(SDL_Renderer* renderer, int x, int y, int character)
{

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	character -= 34;

	if (character < 0)
	{

		return;

	}
	
	for (int r = 0; r < ASCII_CHAR_WH; r++)
	{

		for (int c = 0; c < ASCII_CHAR_WH; c++)
		{

			if (ASCII_FONT_DATA[character][r] & (1 << (ASCII_CHAR_WH - c - 1)))
			{

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

			} else {

				continue;

			}

			
			SDL_RenderDrawPoint(renderer, x + c, y + r);

		}

	}

}


// Use this function inside debug_print, the function meant to be called
// for debugging purposes
void __dbg_print(int x, int y, SDL_Renderer* renderer, char string[DEBUG_STRING_LN])
{

	for (int i = 0; i < DEBUG_STRING_LN; i++)
	{

		if ((int)(string[i]) == 0)
		{

			return;

		}

		draw_char(renderer, x, y, (int)string[i]);
		if (string[i] == '\n')
		{

			y += ASCII_CHAR_WH;
			x = 0;

		} else {

			x += ASCII_CHAR_WH;

		}

	}

}



// This function is where the configuration of your application is intended to be 
// debugged.
void debug_print(SDL_Renderer* renderer, configuration_t* configuration)
{

	// Debug printing logic goes here
	snprintf(__debug_string, DEBUG_LN, "DEBUG PRINT OUT:"); 
	__dbg_print(0, 0, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "MOUSE X: %d", configuration->state_p->mouse_x);
	__dbg_print(0, ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "MOUSE Y: %d", configuration->state_p->mouse_y);
	__dbg_print(0, 2 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "MOUSE LEFT: %s", ((configuration->state_p->lmbtn < 0.0) ? "UP" : "DOWN"));
	__dbg_print(0, 3 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "MOUSE MIDDLE: %s", ((configuration->state_p->mmbtn < 0.0) ? "UP" : "DOWN"));
	__dbg_print(0, 4 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "MOUSE RIGHT: %s", ((configuration->state_p->rmbtn < 0.0) ? "UP" : "DOWN"));
	__dbg_print(0, 5 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "W: %s", ((configuration->state_p->w) ? "DOWN" : "UP"));
	__dbg_print(0, 6 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "A: %s", ((configuration->state_p->a) ? "DOWN" : "UP"));
	__dbg_print(0, 7 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "S: %s", ((configuration->state_p->s) ? "DOWN" : "UP"));
	__dbg_print(0, 8 * ASCII_CHAR_WH, renderer, __debug_string);

	snprintf(__debug_string, DEBUG_LN, "D: %s", ((configuration->state_p->d) ? "DOWN" : "UP"));
	__dbg_print(0, 9 * ASCII_CHAR_WH, renderer, __debug_string);

}




