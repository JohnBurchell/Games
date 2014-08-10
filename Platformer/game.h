#ifndef GAME_H_
#define GAME_H_
#pragma once

#include "common.h"
#include "tileMap.h"
#include "player.h"

#include <SDL.h>

class TileMap;
class Player;

class Game
{
	public:
		Game();
		~Game();

	struct Camera
	{
		explicit Camera(int width, int height) :
			w(width),
			h(height)
		{};
		int x, y;
		int w, h;
	};

	private:
		void run();
		void input();
		void update(int delta);
		void draw(Graphics& graphics, Camera& camera);

		std::unique_ptr<TileMap> map;
		std::unique_ptr<Player> player;
};

#endif //GAME_H_