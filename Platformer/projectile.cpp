#include "projectile.h"

Projectile::Projectile(Graphics& graphics, float x, float y, float velocity) :
	m_x{ x },
	m_y{ y },
	m_velocity{ velocity },
	m_collided{false}
{
	sprite_.reset(new Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 0, 32, 32));
}

void Projectile::draw(Graphics& graphics, float cameraX, float cameraY)
{
	sprite_->draw(graphics, m_x - cameraX, m_y - cameraY);
}

void Projectile::update(uint32_t time_ms, const TileMap& map)
{
	float delta = m_velocity * time_ms;

	auto result = map.getCollisionTilesTest(getDamageRectangle(delta));
	auto collisionResult = getCollisionResult(result, getDamageRectangle(delta));

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
		return BoundingBox{ m_x + 16, m_y + 5, 16 + delta, 5 };
	}
	else
	{
		return BoundingBox{ m_x + 16, m_y + 5 + delta, 16 - delta, 5 };
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
