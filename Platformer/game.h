#ifndef GAME_H_
#define GAME_H_
#pragma once

#include "common.h"
#include "tileMap.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

#include <SDL2/SDL.h>

class TileMap;
class Player;
class Enemy;
class Projectile;

class Game
{
	public:
		Game();
		~Game();

	class Camera
	{
		public:
			explicit Camera(float width, float height) :
				w(width),
				h(height)
			{};
			float x, y;
			float w, h;
	};

	private:
		void run();
		void input();
		void update(uint32_t delta);
		void draw(Graphics& graphics, Camera& camera);
		void updateCamera(Camera& camera);

		std::unique_ptr<TileMap> map;
		std::unique_ptr<Player> player;
		std::unique_ptr<Enemy> enemy;
		std::vector< std::unique_ptr<Projectile> > projectiles;

};

#endif //GAME_H_