#include "projectile.h"

Projectile::Projectile(Graphics& graphics, float x, float y) :

	x_{ x },
	y_{ y }

{
	sprite_.reset(new Sprite(graphics, "resources/sprites/bulletTest.bmp", 0, 32, 32, 32));
}

void Projectile::draw(Graphics& grpahics, float x, float y)
{

}

void Projectile::update(float delta)
{

}

BoundingBox Projectile::getDamageRectangle()
{
	//TODO - Finish implementation of this!
	return BoundingBox{ 0, 0, 0, 0 };
}

Projectile::~Projectile()
{

}