#pragma once

#include <SDL_mixer.h>
#include "common.h"

class Sound
{
public:
	Sound();
	~Sound();

	class Sound_Failure{};

	void play_music();
	void pause_music();
	void stop_music();
	void unpause_music();

private:

	void load_resource(std::string resource_path);

	const std::string music_path = "music/theme.ogg";

	Mix_Music* theme;

};

