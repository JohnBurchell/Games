#ifndef SOUND_H_
#define SOUND_H_

#include <SDL_mixer.h>
#include <memory>

#include "common.h"

class Sound
{
public:
	Sound();
	~Sound();

	class Sound_Failure{};

	//Disable copy
	Sound(const Sound& rhs) = delete;
	Sound operator=(const Sound& rhs) = delete;
	//Disable move
	Sound(Sound&& rhs) = delete;
	Sound operator=(Sound&& rhs) = delete;

	void play_music();
	void pause_music();
	void stop_music();
	void unpause_music();

private:

	void load_resource(std::string resource_path);

	const std::string music_path = "music/theme.ogg";

	std::unique_ptr<Mix_Music*> theme;

};

#endif //SOUND_H_

