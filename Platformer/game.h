#ifndef GAME_H_
#define GAME_H_
#pragma once

#include "common.h"
#include "tileMap.h"
#include "player.h"
#include "enemy.h"
#include "projectile.h"

#ifdef _WIN32
#include <SDL.h>
#endif

#ifdef __linux__
#include <SDL2/SDL.h>
#endif

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

		std::vector< std::unique_ptr<Projectile> > projectiles;
		std::vector< std::unique_ptr<Enemy> > enemies;

};

#endif //GAME_H_