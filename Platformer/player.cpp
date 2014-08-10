#include "player.h"

Player::Player(Graphics& graphics, int x, int y) :

	x_(x),
	y_(y),
	xVelocity{ 10 },
	yVelocity{ 10 },
	width{10}

{
	sprite.reset(new Sprite(graphics, "resources/sprites/player.bmp", 0, 0, 32, 32));
}

void Player::draw(Graphics& graphics, int cameraX, int cameraY)
{
	sprite->draw(graphics, x_ - cameraX, y_ - cameraY);
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			x_ += xVelocity;
			if (x_ >= Constants::LEVEL_WIDTH) {
				x_ -= xVelocity;
			}
			break;
		case SDLK_LEFT:
			x_ -= xVelocity;
			if (x_ <= 0) {
				x_ += xVelocity;
			}
			break;
		case SDLK_DOWN:
			y_ += yVelocity;
			if (y_ > Constants::LEVEL_HEIGHT) {
				y_ -= yVelocity;
			}
			break;
		case SDLK_UP:
			y_ -= yVelocity;
			if (y_ <= 0) {
				y_ += yVelocity;
			}
			break;
		}
	}
}

void Player::update(int delta)
{
	if (y_ < 448) {
		y_ += 1;
	}
}

Player::~Player()
{

}