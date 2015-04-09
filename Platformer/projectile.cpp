#include "projectile.h"

Projectile::Projectile(Graphics& graphics, float x, float y, float velocity) :
	m_x{ x },
	m_y{ y },
	m_velocity{ velocity },
	m_collided{false},
	test{0,0}
{
	if (velocity > 0)
	{
		m_sprite.reset(new Animated_Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 0, Animated_Sprite::sprite_facings::FACING_RIGHT, Animated_Sprite::sprite_poses::MOVING_RIGHT));
	}
	else
	{
		m_sprite.reset(new Animated_Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 0, Animated_Sprite::sprite_facings::FACING_LEFT, Animated_Sprite::sprite_poses::MOVING_LEFT));
	}
}

void Projectile::draw(Graphics& graphics, float cameraX, float cameraY)
{
	//test.draw(graphics, cameraX, cameraY, 6);
	m_sprite->update_sprite();
	m_sprite->draw(graphics, m_x - cameraX, m_y - cameraY);
}

void Projectile::update(uint32_t time_ms, const TileMap& map)
{
	float delta = m_velocity * time_ms;

	auto rect = getDamageRectangle(delta);
	auto result = map.getCollisionTilesTest(rect);
	auto collisionResult = getCollisionResult(result, rect);
	test = BoundingBox{ rect };

	if (collisionResult.collided) {
		m_collided = true;
		m_x = collisionResult.x - getDamageRectangle(delta).width();
	}
	else {
		m_x += delta;
	}
}

bool Projectile::has_collided() const
{
	return m_collided;
}

void Projectile::collision()
{
	m_collided = true;
}

BoundingBox Projectile::getDamageRectangle(float delta) const
{
	if (delta < 0)
	{
		return BoundingBox{ m_x + 5, m_y + 16, delta, 8 };
	}
	else
	{
		return BoundingBox{ m_x + 25, m_y + 13, 5 + delta, 5 };
	}
}

Projectile::CollisionResult Projectile::getCollisionResult(std::vector<TileMap::CollisionTile>& collisionTiles, const BoundingBox& box)
{
	CollisionResult result{ 0, 0, false };
	for (auto& x : collisionTiles) {
		if (x.type_ == TileMap::TileType::WALL) {
			result.collided = true;
			result.x = x.x_;
			result.y = x.y_;
			break;
		}
	}
	return result;
}
