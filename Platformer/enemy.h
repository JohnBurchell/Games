#ifndef ENEMY_H_
#define ENEMY_H_

#ifdef _WIN32
#pragma once
#endif

#include "common.h"
#include "actor.h"

class Graphics;
class TileMap;
class Sprite;

class Enemy : Actor
{
	public:
		Enemy(Graphics& graphics, int x, int y);
		~Enemy();

		void draw(Graphics& graphics, int x, int y);
		void update(const uint32_t time, TileMap& map);

		void updatePlayerData(int x, int y);

	private:

		void updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);
		void updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);

		int x_, y_;
		std::shared_ptr<Sprite> sprite_;
		std::pair<int, int> playerLocation;
};

#endif //ENEMY_H_

//186, 254, 202