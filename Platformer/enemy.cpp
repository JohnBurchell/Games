#include "enemy.h"
#include "player.h"

//TODO - Add more enemies if wanted

class Graphics;
class TileMap;
class Sprite;
class Player;

namespace {

	constexpr float CHASE_SPEED = 0.25f;
}

Enemy::Enemy(Graphics& graphics, int x, int y) :
	x_{ x },
	y_{ y },
	playerLocation{ 0, 0 }
{
	sprite_.reset(new Sprite(graphics, "resources/sprites/enemy.bmp", 0, 0, 32, 32));
}

void Enemy::draw(Graphics& graphics, int cameraX, int cameraY)
{
	sprite_->draw(graphics, x_ - cameraX, y_ - cameraY);
}

void Enemy::update(const uint32_t time_ms, TileMap& map)
{
	//TODO - If i optimise the collection of tiles, this won't be that expensive!
	std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	updateY(time_ms, collisionTiles);
	updateX(time_ms, collisionTiles);
}

void Enemy::updatePlayerData(int x, int y)
{
	playerLocation.first = x;
	playerLocation.second = y;
}

void Enemy::updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	//TODO - Improve, add collision for the enemy
	float yVelocity = 0.0f;

	//Player is above the enemy
	if (playerLocation.second < y_) {
		yVelocity = -CHASE_SPEED;
	}
	else if (playerLocation.second > y_) {
		yVelocity = CHASE_SPEED;
	}

	float delta = yVelocity * time_ms;

	y_ += delta;

}

void Enemy::updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	float xVelocity = 0.0f;

	//Player is above the enemy
	if (playerLocation.first < x_) {
		xVelocity = -CHASE_SPEED;
	}
	else if (playerLocation.first > x_) {
		xVelocity = CHASE_SPEED;
	}

	float delta = xVelocity * time_ms;

	x_ += delta;
}
Enemy::~Enemy()
{

}