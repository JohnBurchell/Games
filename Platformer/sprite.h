#ifndef SPRITE_H_
#define SPRITE_H_
#pragma once

#include <memory>
#include "graphics.h"

class Graphics;

class Sprite 
{
	public:
		Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width);
		~Sprite();

		void draw(Graphics& graphics, float x, float y);
		void update(const int delta);

	private:
		SDL_Texture* texture_;
		SDL_Rect destinationRectangle;

		int x_, y_;
		int width_, height_;

	protected:
		SDL_Rect sourceRectangle;
};

#endif //SPRITE_H_