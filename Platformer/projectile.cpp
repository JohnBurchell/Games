#include "projectile.h"

Projectile::Projectile(Graphics& graphics, float x, float y, float velocity) :
	x_{ x },
	y_{ y },
	velocity_{ velocity },
	collided{false}
{
	sprite_.reset(new Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 0, 32, 32));
}

void Projectile::draw(Graphics& graphics, float cameraX, float cameraY)
{
	sprite_->draw(graphics, x_ - cameraX, y_ - cameraY);
}

void Projectile::update(uint32_t time_ms, const TileMap& map)
{
	float delta = velocity_ * time_ms;

	auto result = map.getCollisionTilesTest(getDamageRectangle(delta));
	auto collisionResult = getCollisionResult(result, getDamageRectangle(delta));

	if (collisionResult.collided) {
		collided = true;
		x_ = collisionResult.x - getDamageRectangle(delta).width();
		system("pause");
	}
	else {
		x_ += delta;
	}
}

bool Projectile::hasCollided() const
{
	return collided;
}

void Projectile::collision()
{
	collided = true;
}

BoundingBox Projectile::getDamageRectangle(float delta) const
{
	if (delta < 0)
	{
		return BoundingBox{ x_ + 16, y_ + 5, 16 + delta, 5 };
	}
	else
	{
		return BoundingBox{ x_ + 16, y_ + 5 + delta, 16 - delta, 5 };
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

Projectile::~Projectile()
{

}