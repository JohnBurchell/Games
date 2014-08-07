#include "player.h"

Player::Player(Graphics& graphics, int x, int y)
{
	sprite.reset(new Sprite(graphics, "resources/sprites/player.bmp", 0, 0, 32, 32));
	x_ = x;
	y_ = y;
}

void Player::draw(Graphics& graphics)
{
	//This should probably be changed later, transposing into other co-ords
	sprite->draw(graphics, x_ * 32, y_ * 32);
}

void Player::update(int delta)
{
	//TODO - Update player on movement
}

Player::~Player()
{

}