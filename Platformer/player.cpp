#include "player.h"

namespace {

	const float Y_VELOCITY = 3.0f;
	const float X_VELOCTIY = 3.0f;

	const BoundingBox COLLISION_Y(10, 2, 12, 30);
	const BoundingBox COLLISION_X(6, 10, 20, 12);
}

using std::vector;

Player::Player(Graphics& graphics, int x, int y) :

	xVelocity{ 10 },
	yVelocity{ 10 }
{
	sprite.reset(new Sprite(graphics, "resources/sprites/player.bmp", 0, 0, 32, 32));
	box_.x = (x);
	box_.y = (y);
	box_.w = Constants::TILE_WIDTH;
	box_.h = Constants::TILE_HEIGHT;
}

void Player::draw(Graphics& graphics, int cameraX, int cameraY)
{
	sprite->draw(graphics, box_.x - cameraX, box_.y - cameraY);

	BoundingBox bottom{
		box_.x + COLLISION_Y.left(),
		box_.y + COLLISION_Y.top() + COLLISION_Y.height() / 2,
		COLLISION_Y.width(),
		COLLISION_Y.height() / 2 };

	BoundingBox left{
		box_.x + COLLISION_X.left(),
		box_.y + COLLISION_X.top(),
		COLLISION_X.width() / 2,
		COLLISION_X.height() };

	BoundingBox right{
		box_.x + COLLISION_X.left() + COLLISION_X.width() / 2,
		box_.y + COLLISION_X.top(),
		COLLISION_X.width() / 2,
		COLLISION_X.height() };

	BoundingBox top{
		box_.x + COLLISION_Y.left(),
		box_.y + COLLISION_Y.top(),
		COLLISION_Y.width(),
		COLLISION_Y.height() / 2 };

	bottom.draw(graphics, cameraX, cameraY);
	left.draw(graphics, cameraX, cameraY);
	right.draw(graphics, cameraX, cameraY);
	top.draw(graphics, cameraX, cameraY);

	//for (auto& x : collisionTiles) {
	//	x.draw(graphics, cameraX, cameraY);
	//}

}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			box_.x += xVelocity;
			if (box_.x >= Constants::LEVEL_WIDTH) {
				box_.x -= xVelocity;
			}
			break;
		case SDLK_LEFT:
			box_.x -= xVelocity;
			if (box_.x <= 0) {
				box_.x += xVelocity;
			}
			break;
		case SDLK_DOWN:
			box_.y += yVelocity;
			if (box_.y > Constants::LEVEL_HEIGHT) {
				box_.y -= yVelocity;
			}
			break;
		case SDLK_UP:
			box_.y -= yVelocity;
			if (box_.y <= 0) {
				box_.y += yVelocity;
			}
			break;
		}
	}
}

void Player::update(int time_ms, TileMap& map)
{
	updateY(time_ms, map);
	updateX(time_ms, map);
}

BoundingBox Player::bottomCollision(const int delta) const
{
	return BoundingBox(
		box_.x + COLLISION_Y.left(),
		box_.y + COLLISION_Y.top() + COLLISION_Y.height() / 2,
		COLLISION_Y.width(),
		COLLISION_Y.height() / 2 + delta);
}

BoundingBox Player::leftCollision(const int delta) const
{
	return BoundingBox(
		box_.x + COLLISION_X.left() + delta,
		box_.y + COLLISION_X.top(),
		COLLISION_X.width() / 2 - delta,
		COLLISION_X.height());
}
BoundingBox Player::rightCollision(const int delta) const
{
	return BoundingBox(
		box_.x + COLLISION_X.left() + COLLISION_X.width() / 2,
		box_.y + COLLISION_X.top(),
		COLLISION_X.width() / 2 + delta,
		COLLISION_X.height());
}
BoundingBox Player::topCollision(const int delta) const
{
	return BoundingBox(
		box_.x + COLLISION_Y.left() + delta,
		box_.y + COLLISION_Y.top(),
		COLLISION_Y.width(),
		COLLISION_Y.height() / 2 - delta);
}


bool Player::testCollision(BoundingBox& a, BoundingBox& b) const
{
	return false;
}

void Player::updateX(int time_ms, TileMap& map)
{
	//TODO - Perform X axis updates of movement and jumping.

	auto collisionTiles = map.getCollisionTiles(rightCollision(time_ms));

	for (auto& x : collisionTiles) {
		if (x.type_ == TileMap::TileType::WALL) {
			std::cout << "RIGHT collided!" << std::endl;
		}
	}

	collisionTiles = map.getCollisionTiles(leftCollision(time_ms));
	for (auto& x : collisionTiles) {
		if (x.type_ == TileMap::TileType::WALL) {
			std::cout << "LEFT collided!" << std::endl;
		}
	}
}

void Player::updateY(int time_ms, TileMap& map)
{
	if (box_.y < 450) {
		box_.y += Y_VELOCITY;
	}

	auto collisionTiles = map.getCollisionTiles(bottomCollision(time_ms));

	for (auto& x : collisionTiles) {
		if (x.type_ == TileMap::TileType::WALL) {
			std::cout << "Bottom collided!" << std::endl;
		}
	}

	collisionTiles = map.getCollisionTiles(topCollision(time_ms));
	for (auto& x : collisionTiles) {
		if (x.type_ == TileMap::TileType::WALL) {
			std::cout << "Top collided!" << std::endl;
		}
	}
}

Player::~Player()
{

}