#ifndef PLAYER_H_
#define PLAYER_H_
#pragma once

#include "common.h"
#include "sprite.h"
#include "graphics.h"

class Graphics;

class Player
{
	public:

		Player(Graphics& graphics, int x, int y);
		~Player();

		void draw(Graphics& graphics);
		void update(const int delta);

		int x_, y_;

	private:
		//This will have to be animated later!
		std::unique_ptr<Sprite> sprite;
};

#endif //PLAYER_H_