
#ifndef SOUND_H
#define SOUND_H

#include "configuration.h"
#include "libsinternal.h"

void play_sfx(Mix_Chunk* sfx, int channel_id);
void play_music(Mix_Music* music, bool* set_playing);
void handle_audio(configuration_t* configuration, sdl_t* sdl);


#endif // SOUND_H