#ifndef INPUT_H_
#define INPUT_H_

#ifdef _WIN32
#pragma once
#include "SDL.h"
#endif

#ifdef linux
#include "SDL2/SDL.h"
#endif

#include "common.h"
#include "player.h"

#include <unordered_map>


//TODO - Perhaps abstract player so that it's an actor so I can make this more generic later in the game?
class Command
{
	virtual ~Command();
	virtual void execute(Player& player) = 0;
};

class InputHandler
{
	public:
		InputHandler();
		~InputHandler();

		void handleInput();

	private:

		bool isKeyPressed(SDL_Keycode& key);
		bool isKeyReleased(SDL_Keycode& key);
		bool isKeyHeld(SDL_Keycode& key);

		void keyPressed(SDL_Keycode& key);
		void keyReleased(SDL_Keycode& key);

		std::unordered_map < SDL_Keycode, bool> pressedKeys;
		std::unordered_map < SDL_Keycode, bool> releasedKeys;
		std::unordered_map < SDL_Keycode, bool> heldKeys;
};


#endif //INPUT_H_