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

		void draw(Graphics& graphics, float cameraX, float cameraY);
		void update(uint32_t time_ms, const TileMap& map);
	
		BoundingBox getDamageRectangle(float delta) const;

		inline float getPos() { return m_x; };

		bool has_collided() const;
		void collision();

	private:
		float m_x, m_y, m_velocity;
		bool m_collided;

		struct CollisionResult
		{
			float x, y;
			bool collided;
		};

		CollisionResult getCollisionResult(std::vector<TileMap::CollisionTile>& collisionTiles, const BoundingBox& box);

		std::shared_ptr<Sprite> sprite_;
};

#endif //PROJECTILE_H_