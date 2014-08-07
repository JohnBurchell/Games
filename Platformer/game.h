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

		class Camera {

		public:
			Camera(int x, int y) :
				camera_x(x),
				camera_y(y)
			{}

			void update(int x, int y) { camera_x = x; camera_y = y; };
			inline int getCamera_x() { return camera_x; };
			inline int getCamera_y() { return camera_y; };

		private:

			int camera_x;
			int camera_y;
		};

	private:
		void run();
		void input();
		void update();
		void draw();

		std::unique_ptr<TileMap> map;
		std::unique_ptr<Player> player;
};

#endif //GAME_H_