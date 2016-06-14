#include "input.h"

InputHandler::InputHandler()
{

}

void InputHandler::handleInput()
{
	SDL_Event SDLevent;

	while (SDL_PollEvent(&SDLevent) != 0) {

		if (SDLevent.type == SDL_KEYDOWN){
			pressedKeys[SDLevent.key.keysym.sym] = true;
		}
		else if (SDLevent.type == SDL_KEYUP){
			releasedKeys[SDLevent.key.keysym.sym] = true;
		}
	}
}

bool InputHandler::isKeyPressed(SDL_Keycode& key)
{
	return pressedKeys[key];
}

bool InputHandler::isKeyHeld(SDL_Keycode& key)
{
	return heldKeys[key];
}

bool InputHandler::isKeyReleased(SDL_Keycode& key)
{
	return releasedKeys[key];
}

void InputHandler::keyPressed(SDL_Keycode& key)
{

}

void InputHandler::keyReleased(SDL_Keycode& key)
{

}

InputHandler::~InputHandler()
{

}