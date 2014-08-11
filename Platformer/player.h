#ifndef PLAYER_H_
#define PLAYER_H_
#pragma once

#include "common.h"
#include "sprite.h"
#include "graphics.h"
#include "boundingBox.h"
#include "tileMap.h"

class Graphics;
class TileMap;

class Player
{
	public:

		Player(Graphics& graphics, int x, int y);
		~Player();

		void draw(Graphics& graphics, int cameraX, int cameraY);
		void update(const int delta, TileMap& map);

		inline int getXpos() { return box_.x; };
		inline int getYpos() { return box_.y; };

		void handleEvent(SDL_Event& e);

	private:

		int xVelocity, yVelocity;
		SDL_Rect box_;

		friend bool operator<(Player& a, Player& b);

		void updateX(const int delta, TileMap& map);
		void updateY(const int delta, TileMap& map);


		BoundingBox bottomCollision(const int delta) const;
		BoundingBox topCollision(const int delta) const;
		BoundingBox rightCollision(const int delta) const;
		BoundingBox leftCollision(const int delta) const;


		bool testCollision(BoundingBox& a, BoundingBox& b) const;
		bool touchesWall(BoundingBox& a);

		//This will have to be animated later!
		std::unique_ptr<Sprite> sprite;
		std::vector<TileMap::CollisionTile> collisionTiles;
};

#endif //PLAYER_H_