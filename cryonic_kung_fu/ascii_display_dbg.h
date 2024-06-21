
#ifndef ASCII_DISPLAY_DBG_H
#define ASCII_DISPLAY_DBG_H

#define DEBUG_YES_H

#include <SDL2/SDL.h>
#include <assert.h>
#include "configuration.h"



#define ASCII_CHAR_WH   8
#define ASCII_CHAR_NM   61
#define DEBUG_STRING_LN 512
#define DEBUG_LN 511

extern const int ASCII_FONT_DATA[ASCII_CHAR_NM][ASCII_CHAR_WH];

extern char __debug_string[DEBUG_STRING_LN];

void draw_char(SDL_Renderer* renderer, int x, int y, int character);
void __dbg_print(int x, int y, SDL_Renderer* renderer, char string[DEBUG_STRING_LN]);
void debug_print(SDL_Renderer* renderer, configuration_t* configuration);

#endif // ASCII_DISPLAY_DBG_H