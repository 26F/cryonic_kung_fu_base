
#include "sound.h"

void play_sfx(Mix_Chunk* sfx, int channel_id)
{


	// play sound effect using next available channel
	// for layered sound recommend using different channels.
	Mix_PlayChannel(channel_id, sfx, 0);

}



void play_music(Mix_Music* music, bool* set_playing)
{

	assert(set_playing);
	*set_playing = true;
	// -1 is for loop true, zero for loop false 0
	// for not looping
	Mix_PlayMusic(music, -1);

	// associated functions: 
	// Mix_PauseMusic()
	// Mix_HaltMusic()
	// Mix_ResumeMusic()
}


// The configuration of the application logically determines
// which audio should be playing. We handle this logic here
void handle_audio(configuration_t* configuration, sdl_t* sdl)
{


	if (configuration->is_shooting && configuration->last_shot_t == 0)
	{

		play_sfx(sdl->gun_sfx1.sfx, sdl->gun_sfx1.channel_id);

	}

	// Incomplete example of illustrating music change
	if (configuration->music_change && (!(sdl->boss_battle.is_playing)))
	{

		configuration->music_change = false;
		Mix_HaltMusic();
		play_music(sdl->boss_battle.track, &sdl->boss_battle.is_playing);

	}

}