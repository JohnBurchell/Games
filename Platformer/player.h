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

		void draw(Graphics& graphics, int cameraX, int cameraY);
		void update(const int delta);

		inline int getXpos() { return x_; };
		inline int getYpos() { return y_; };

		void handleEvent(SDL_Event& e);

	private:
		int x_, y_;
		int xVelocity, yVelocity;
		int width;

		//This will have to be animated later!
		std::unique_ptr<Sprite> sprite;
};

#endif //PLAYER_H_