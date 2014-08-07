#ifndef SPRITE_H_
#define SPRITE_H_
#pragma once

#include <memory>
#include "graphics.h"

class Graphics;

/*
	Creates a basic sprite from a given file path.

	/*Param 1 : Graphics reference
	/*Param 2 : std::string filepath
	/*Param 3 : int - x position in the sprite_sheet
	/*Param 4 : int - y position in the sprite_sheet
	/*Param 5 : int - width of the sprite
	/*Param 6 : int - height of the sprite
*/
class Sprite 
{
	public:
		Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width);
		~Sprite();

		void draw(Graphics& graphics, int x, int y);
		void update(const int delta);

	protected:
		SDL_Rect sourceRectangle;

	private:
		SDL_Texture* texture_;
		SDL_Rect destinationRectangle;

		int x_, y_, width_, height_;
};

#endif //SPRITE_H_