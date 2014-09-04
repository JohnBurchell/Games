#ifndef PLAYER_H_
#define PLAYER_H_
#pragma once

#include "common.h"
#include "boundingBox.h"
#include "actor.h"

class Grpahics;
class TileMap;

class Player : public Actor
{
	public:

		Player(Graphics& graphics, float x, float y);
		~Player() override;

		void draw(Graphics& graphics, float cameraX, float cameraY) override;
		void update(const uint32_t delta, TileMap& map) override;

		BoundingBox getDamageRectangle();

		inline float getXpos() { return x_; };
		inline float getYpos() { return y_; };

		void takeDamage();
		void startJump();
		void startMovingLeft();
		void startMovingRight();
		void stopMoving();
		void shoot();

		void enableDebug();

	private:

		struct CollisionResult
		{
			float x, y;
			bool collided;
		};

		float x_, y_;
		float xVelocity, yVelocity;
		int accelerationX;
		bool onGround, jumping;

		friend bool operator<(Player& a, Player& b);

		void updateX(const uint32_t delta, std::vector<BoundingBox>& collisionTiles);
		void updateY(const uint32_t delta, std::vector<BoundingBox>& collisionTiles);

		BoundingBox rightCollisionBox(float delta) const;
		BoundingBox leftCollisionBox(float delta) const;
		BoundingBox topCollisionBox(float delta) const;
		BoundingBox bottomCollisionBox(float delta) const;

		CollisionResult getCollisionResult(std::vector<BoundingBox>& collidingTiles, BoundingBox& box);

		//This will have to be animated later!
		std::unique_ptr<Sprite> sprite;

		std::vector<BoundingBox> debugTiles;
		bool debug;
		float debugDelta;
};

#endif //PLAYER_H_