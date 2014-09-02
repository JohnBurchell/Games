#include "enemy.h"
#include "player.h"

//TODO - Add more enemies if wanted

class Graphics;
class TileMap;
class Sprite;
class Player;

namespace {

	constexpr float CHASE_SPEED = 0.15f;

	BoundingBox Y_BOX = { 10, 2, 12, 30 };
	BoundingBox X_BOX = { 6, 10, 20, 12 };
}

Enemy::Enemy(Graphics& graphics, float x, float y) :
	x_{ x },
	y_{ y },
	onGround{ false }
{
	sprite_.reset(new Sprite(graphics, "resources/sprites/enemy.bmp", 0, 0, 32, 32));
	playerLocation = { 0, 0 };
}

void Enemy::draw(Graphics& graphics, float cameraX, float cameraY)
{
	sprite_->draw(graphics, x_ - cameraX, y_ - cameraY);

	BoundingBox y = { x_ + Y_BOX.left(), y_ + Y_BOX.top(), Y_BOX.width(), Y_BOX.height() };
	BoundingBox x = { x_ + X_BOX.left(), y_ + X_BOX.top(), X_BOX.width(), X_BOX.height() };
	y.draw(graphics, cameraX, cameraY, 4);
	x.draw(graphics, cameraX, cameraY, 4);
}

void Enemy::update(const uint32_t time_ms, TileMap& map)
{
	//TODO - If i optimise the collection of tiles, this won't be that expensive!
	std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	updateY(time_ms, collisionTiles);
	updateX(time_ms, collisionTiles);
}

void Enemy::updatePlayerData(float x, float y)
{
	playerLocation.playerX = x;
	playerLocation.playerY = y;
}

void Enemy::updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	//TODO - Improve, add collision for the enemy
	float yVelocity = 0.0f;

	//Player is above the enemy
	//if (playerLocation.playerY < y_) {
	//	yVelocity = -CHASE_SPEED;
	//}
	//else if (playerLocation.playerY > y_) {
	//	yVelocity = CHASE_SPEED;
	//}

	if (!onGround) {
		yVelocity = 0.25f;
	}

	float delta = yVelocity * time_ms;

	//Going down
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, bottomCollisionBox(delta));

		if (result.collided) {
			y_ = result.y - Y_BOX.bottom();
			yVelocity = 0.0f;
			onGround = true;
		}
		else {
			y_ += delta;
			onGround = false;
		}
	}
	//Going up
	else {
		auto result = getCollisionResult(collisionTiles, topCollisionBox(delta));

		if (result.collided) {
			y_ = result.y + Y_BOX.height();
			yVelocity = 0.0f;
		}
		else {
			y_ += delta;
			onGround = false;
		}
	}
}

void Enemy::updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	float xVelocity = 0.0f;

	//Player is to the left of the enemy
	if (playerLocation.playerX < x_) {
		xVelocity = -CHASE_SPEED;
	}
	//Player to the right
	else if (playerLocation.playerX > x_) {
		xVelocity = CHASE_SPEED;
	}

	float delta = xVelocity * time_ms;

	//Going to the right
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, rightCollisionBox(delta));

		if (result.collided) {
			xVelocity = 0.0f;
			x_ = result.x - X_BOX.right();
		}
		else {
			x_ += delta;
		}
	}
	//Going left
	else {
		auto result = getCollisionResult(collisionTiles, leftCollisionBox(delta));

		if (result.collided) {
			xVelocity = 0.0f;
			x_ = result.x + X_BOX.right();
		}
		else {
			x_ += delta;
		}
	}
}

BoundingBox Enemy::leftCollisionBox(float delta) const
{
	return BoundingBox{
		x_ + X_BOX.left() + delta,
		y_ + X_BOX.top(),
		X_BOX.width() / 2 - delta,
		X_BOX.height() };
}

BoundingBox Enemy::rightCollisionBox(float delta) const
{
	return BoundingBox{
		x_ + +X_BOX.left() + X_BOX.width() / 2,
		y_ + X_BOX.top(),
		X_BOX.width() / 2 + delta,
		X_BOX.height() };
}

BoundingBox Enemy::topCollisionBox(float delta) const
{
	return BoundingBox{
		x_ + Y_BOX.left(),
		y_ + Y_BOX.top() + delta,
		Y_BOX.width(),
		Y_BOX.height() / 2 - delta };
}

BoundingBox Enemy::bottomCollisionBox(float delta) const
{
	return BoundingBox{
		x_ + Y_BOX.left(),
		y_ + Y_BOX.top() + Y_BOX.height() / 2,
		Y_BOX.width(),
		Y_BOX.height() / 2 + delta };
}

Enemy::CollisionResult Enemy::getCollisionResult(std::vector<BoundingBox>& collisionTiles, BoundingBox& box)
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

BoundingBox Enemy::getDamageRectangle()
{
	return{ x_ + X_BOX.left(), y_ + Y_BOX.top(), X_BOX.width(), X_BOX.height() };
}

Enemy::~Enemy()
{

}