#ifndef SPRITE_H_
#define SPRITE_H_
#pragma once

#include <memory>
#include "graphics.h"

class Graphics;

class Sprite 
{
	public:
		explicit Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width);

		void draw(Graphics& graphics, float x, float y);
		void update(const int delta);

	private:
		SDL_Texture* m_texture;
		SDL_Rect m_destination_rectangle;

		int m_x, m_y;
		int m_width, m_height;

	protected:
		SDL_Rect m_source_rectangle;
};

#endif //SPRITE_H_