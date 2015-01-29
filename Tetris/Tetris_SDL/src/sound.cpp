#include "sound.h"

Sound::Sound()
{
	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) 	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << "\n";
		throw Sound_Failure();
	}

	//Load music
	theme = Mix_LoadMUS(music_path.c_str());
	if (theme == nullptr)
	{
		std::cout << "SDL_mixer could not open the file" << music_path << "! SDL_mixer Error: " << Mix_GetError() << "\n";
	}
}

void Sound::play_music()
{
	Mix_PlayMusic(theme, -1);
}
void Sound::pause_music()
{
	if (!Mix_PausedMusic()) {
		Mix_PauseMusic();
	}
}
void Sound::unpause_music()
{
	if (Mix_PausedMusic()) {
		Mix_ResumeMusic();
	}
}
void Sound::stop_music()
{
	Mix_HaltMusic();
}
Sound::~Sound()
{
	if (Mix_PlayingMusic()){
		Mix_HaltMusic();
	}

	Mix_FreeMusic(theme);
	Mix_Quit();
}
