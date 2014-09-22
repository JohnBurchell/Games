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

		inline const vector2d getPosition() const { return position; };

		//Remove - Replace with sprite facing when animation is implemented?
		inline float getVelocity() { return xVelocity; };

		void takeDamage();
		void startJump();
		void startMovingLeft();
		void startMovingRight();
		void stopMoving();
		void shoot();

		void enableDebug();

	private:

		vector2d position;

		struct CollisionResult
		{
			float x, y;
			bool collided;
		};

		float xVelocity, yVelocity;
		int accelerationX, health;
		bool onGround, jumping, invulnerable;
		float invulnTime;

		friend bool operator<(Player& a, Player& b);

		void updateX(const uint32_t delta, std::vector<BoundingBox>& collisionTiles);
		void updateY(const uint32_t delta, std::vector<BoundingBox>& collisionTiles);

		BoundingBox rightCollisionBox(float delta) const;
		BoundingBox leftCollisionBox(float delta) const;
		BoundingBox topCollisionBox(float delta) const;
		BoundingBox bottomCollisionBox(float delta) const;

		CollisionResult getCollisionResult(std::vector<BoundingBox>& collidingTiles, const BoundingBox& box);

		//This will have to be animated later!
		std::unique_ptr<Sprite> sprite;

		std::vector<BoundingBox> debugTiles;
		float debugDelta;
		bool debug;
};

#endif //PLAYER_H_