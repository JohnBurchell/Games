#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "common.h"
#include "graphics.h"
#include "sprite.h"
#include "boundingBox.h"
#include "tileMap.h"

class Graphics;
class Sprite;
class TileMap;

class Projectile
{

	public:
		Projectile(Graphics& graphics, float x, float y, float velocity);
		~Projectile();

		void draw(Graphics& graphics, float cameraX, float cameraY);
		void update(uint32_t time_ms, const TileMap& map);
	
		BoundingBox getDamageRectangle(float delta) const;

		inline float getPos() { return x_; };

		bool hasCollided() const;
		void collision();

	private:
		float x_, y_, velocity_;
		bool collided;

		struct CollisionResult
		{
			float x, y;
			bool collided;
		};

		CollisionResult getCollisionResult(std::vector<TileMap::CollisionTile>& collisionTiles, const BoundingBox& box);

		std::shared_ptr<Sprite> sprite_;
};

#endif //PROJECTILE_H_