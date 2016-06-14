#ifndef SOUND_H_
#define SOUND_H_

#include <SDL_mixer.h>
#include <memory>
#include <string>
#include <unordered_map>

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
	void change_sound_level(const int value);
	void init_sounds();

	void load_sound(const char* path, const char* type);
	void play_sound(const char* type);

private:

	const std::string music_path = "music/theme.ogg";

	int m_sound_level;
	bool m_playing;

	std::unique_ptr<Mix_Music*> theme;
	std::unordered_map<const char*, Mix_Chunk*> m_sounds;

};

#endif //SOUND_H_

