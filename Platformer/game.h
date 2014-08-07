#ifndef GAME_H_
#define GAME_H_
#pragma once

#include "common.h"
#include "tileMap.h"

#include <SDL.h>

class TileMap;

class Game
{
	public:
		Game();
		~Game();

	private:
		void run();
		void input();
		void update();
		void draw();

		std::unique_ptr<TileMap> map;
};

#endif //GAME_H_