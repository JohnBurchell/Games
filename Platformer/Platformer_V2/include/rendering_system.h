#ifndef RENDERING_SYSTEM_H_
#define RENDERING_SYSTEM_H_

#include "system.h"
#include <SDL.h>
#include <string>

class Rendering_System : System
{
	//This system should be able to render anything passed to it. Maybe still make this a singleton?
	void render_texture(SDL_Texture* texture, const SDL_Rect destination, const SDL_Rect* clip = nullptr) const;
	void render_texture(SDL_Texture* texture, const float x, const float y, const SDL_Rect* clip = nullptr) const;
	void update_FPS(const std::string fps);

	//REMOVE LATER - Debugging
	void render_rectanlge(const float pos_x, const float pos_y, const int colour, int width = 32, int height = 32);
	void render_line(float origin_x, float origin_y, float target_x, float target_y);

	void flip();
	void clear();

private:

	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif //RENDERING_SYSTEM_H_