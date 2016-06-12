#include "sound.h"
#include <iostream>

Sound::Sound() : m_sound_level(MIX_MAX_VOLUME)
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 	
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
		throw Sound_Failure();
	}

	//Load music
	theme = std::make_unique<Mix_Music*>(Mix_LoadMUS(music_path.c_str()));
	if (theme == nullptr)
	{
		std::cout << "SDL_mixer could not open the file" << music_path << "! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

void Sound::play_music()
{
	Mix_PlayMusic(*theme, -1);
	m_playing = true;
}

void Sound::pause_music()
{
	if (!Mix_PausedMusic()) 
	{
		Mix_PauseMusic();
	}
}

void Sound::unpause_music()
{
	if (Mix_PausedMusic()) 
	{
		Mix_ResumeMusic();
	}
}

void Sound::change_sound_level(const int value)
{
	//Change sound level to this level - default behaviour is to turn it off
	Mix_VolumeMusic(value);
}

void Sound::stop_music()
{
	Mix_HaltMusic();
}

Sound::~Sound()
{
	if (Mix_PlayingMusic())
	{
		Mix_HaltMusic();
	}
	Mix_FreeMusic(*theme);
	Mix_Quit();
}
