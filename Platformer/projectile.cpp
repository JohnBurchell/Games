#include "Projectile.h"

namespace {

}

Projectile::Projectile(Graphics& graphics, float x, float y, float velocity) :
	x_{ x },
	y_{ y },
	velocity_{ velocity }
{
	sprite_.reset(new Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 0, 32, 32));
}

void Projectile::draw(Graphics& graphics, float cameraX, float cameraY)
{
	sprite_->draw(graphics, x_ - cameraX, y_ - cameraY);
}

void Projectile::update(uint32_t time_ms, const TileMap& map)
{
	//std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	float delta = velocity_ * time_ms;

	//Going right
	if (delta > 0){

	}
	//Going left
	else {

	}

	x_ += delta;
}

bool Projectile::hasCollided() const
{
	return collided;
}

BoundingBox Projectile::getDamageRectangle() const
{
	return BoundingBox{ x_ + 16, y_ + 5, 16, 5 };
}

Projectile::CollisionResult Projectile::getCollisionResult(std::vector<BoundingBox>& collisionTiles, BoundingBox& box)
{
	CollisionResult result{ 0, 0, false };

	for (auto& x : collisionTiles) {
		if (box.boxCollision(x)) {
			result.collided = true;
			result.x = x.left();
			result.y = x.top();
			break;
		}
	}
	return result;
}

Projectile::~Projectile()
{

}