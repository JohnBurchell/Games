#ifndef BACKGROUND_H_
#define BACKGROUND_H_
#pragma once

#include "common.h"
#include "graphics.h"

class Graphics;

class Background
{	
	public:
		Background(Graphics& graphics);
		~Background();

	private:
		SDL_Texture* texture;
};


#endif //BACKGROUND_H_