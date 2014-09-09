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
		Enemy(Graphics& graphics, float x, float y);
		~Enemy() override;

		void draw(Graphics& graphics, float x, float y) override;
		void update(const uint32_t time, TileMap& map) override;

		void updatePlayerData(float x, float y);
		BoundingBox getDamageRectangle();

	private:

		void updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);
		void updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);
		bool onGround;

		struct CollisionResult
		{
			float x, y;
			bool collided;
		};

		BoundingBox rightCollisionBox(float delta) const;
		BoundingBox leftCollisionBox(float delta) const;
		BoundingBox topCollisionBox(float delta) const;
		BoundingBox bottomCollisionBox(float delta) const;

		void takeDamage(int damage);

		CollisionResult getCollisionResult(const std::vector<BoundingBox>& collidingTiles, const BoundingBox& box);

		float x_, y_;
		int health;
		std::shared_ptr<Sprite> sprite_;

		struct PlayerLocation
		{
			float playerX, playerY;
		};

		PlayerLocation playerLocation;

};

#endif //ENEMY_H_

//186, 254, 202