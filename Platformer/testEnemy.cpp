#include "testEnemy.h"

TestEnemy::TestEnemy(Graphics& graphics)
{
	graphics_ = &graphics;
	if (graphics_ == nullptr)
	{
		//Throw?
	}
	sprite_.reset(new Sprite(graphics, "resources/sprites/enemy.bmp", 0, 0, 32, 32));
}

void TestEnemy::draw()
{
	sprite_->draw(*graphics_, 200, 200);
}

void TestEnemy::update(float elapsed_time)
{

}
