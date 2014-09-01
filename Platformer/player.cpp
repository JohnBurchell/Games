#include "player.h"
#include <algorithm>
#include <assert.h>

using std::vector;

//Gravity = 2 * max jump height / time to apex

//Initial jump velocity = 2 * gravity * height at max jump

namespace {
	

	constexpr float JUMP_SPEED = 0.25f;

	constexpr float INITIAL_JUMP_VELOCITY = -0.85f;

	constexpr float GRAVITY = 0.00345f;

	constexpr float Y_TARGETSPEED = 0.55f;
	constexpr float X_TARGETSPEED = 0.25f;

	//The boxes should be a little bit bigger than the player sprite
	BoundingBox Y_BOX = { 10, 2, 12, 30 };
	BoundingBox X_BOX = { 6, 10, 20, 12 };
}

Player::Player(Graphics& graphics, float x, float y) :

	x_{ x },
	y_{ y },
	xVelocity{ 0.0f },
	yVelocity{ 0.0f },
	accelerationX{ 0 },
	debug{ false },
	jumping{ false },
	debugDelta{ 0.0f }
{
	sprite.reset(new Sprite(graphics, "resources/sprites/player.bmp", 0, 0, 32, 32));
}

void Player::draw(Graphics& graphics, int cameraX, int cameraY)
{
	sprite->draw(graphics, static_cast<int>(x_ - cameraX), static_cast<int>(y_ - cameraY));

	if (debug) {
		for (auto& x : debugTiles) {
			x.draw(graphics, cameraX, cameraY);
		}

		//if (debugDelta <= 0.0f) {
		//	BoundingBox left = leftCollisionBox(debugDelta);
		//	left.draw(graphics, cameraX, cameraY, 2);
		//	BoundingBox top = topCollisionBox(debugDelta);
		//	top.draw(graphics, cameraX, cameraY, 5);
		//}
		//else if (debugDelta >= 0.0f) {
		//	BoundingBox right = rightCollisionBox(debugDelta);
		//	right.draw(graphics, cameraX, cameraY, 6);
		//	BoundingBox bottom = bottomCollisionBox(debugDelta);
		//	bottom.draw(graphics, cameraX, cameraY, 4);
		//}

		BoundingBox y = { x_ + Y_BOX.left(), y_ + Y_BOX.top(), Y_BOX.width(), Y_BOX.height() };
		BoundingBox x = { x_ + X_BOX.left(), y_ + X_BOX.top(), X_BOX.width(), X_BOX.height() };
		y.draw(graphics, cameraX, cameraY, 2);
		x.draw(graphics, cameraX, cameraY, 2);
	}
}

void Player::handleEvent(SDL_Event& e)
{
	if (e.type == SDL_KEYDOWN){
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			accelerationX = 1;
			break;
		case SDLK_LEFT:
			accelerationX = -1;
			break;
		case SDLK_DOWN:
			break;
		case SDLK_UP:
			if (onGround) {
				yVelocity = INITIAL_JUMP_VELOCITY;
			}
			break;
		case SDLK_F12:
			debug = !debug;
			break;
		}
	}
	if (e.type == SDL_KEYUP) {
		switch (e.key.keysym.sym) {
		case SDLK_RIGHT:
			accelerationX = 0;
			xVelocity = 0;
			break;
		case SDLK_LEFT:
			accelerationX = 0;
			xVelocity = 0;
			break;
		}
	}
}

void Player::update(uint32_t time_ms, TileMap& map)
{
	std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	if (debug) {
		debugTiles = map.getCollisionTiles();
	}

	updateY(time_ms, collisionTiles);
	updateX(time_ms, collisionTiles);
}

BoundingBox Player::leftCollisionBox(float delta) const
{
	return BoundingBox{ 
		x_ + X_BOX.left() + delta, 
		y_ + X_BOX.top(), 
		X_BOX.width() / 2 - delta, 
		X_BOX.height() };
}

BoundingBox Player::rightCollisionBox(float delta) const
{
	return BoundingBox{ 
		x_ + + X_BOX.left() + X_BOX.width() / 2, 
		y_ + X_BOX.top(), 
		X_BOX.width() / 2 + delta, 
		X_BOX.height()};
}

BoundingBox Player::topCollisionBox(float delta) const
{
	return BoundingBox{ 
		x_ + Y_BOX.left(), 
		y_ + Y_BOX.top() + delta, 
		Y_BOX.width(), 
		Y_BOX.height() / 2 - delta};
}

BoundingBox Player::bottomCollisionBox(float delta) const
{
	return BoundingBox{ 
		x_ + Y_BOX.left(), 
		y_ + Y_BOX.top() + Y_BOX.height() / 2, 
		Y_BOX.width(),
		Y_BOX.height() / 2 + delta};
}

Player::CollisionResult Player::getCollisionResult(std::vector<BoundingBox>& collisionTiles, BoundingBox& box)
{
	CollisionResult result{ 0, 0, false };

	for (auto& x : collisionTiles) {
		if (testCollision(x, box)) {
			result.collided = true;
			result.x = x.left();
			result.y = x.top();
			break;
		}
	}
	return result;
}

void Player::updateX(uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	//TODO - Perform X axis updates of movement and jumping.

	// Euler Integration
	//position += velocity * deltaTime
	//velocity += acceleration * deltaTime
	float acceleration_x_ = 0.0f;

	if (accelerationX < 0) acceleration_x_ = onGround ? -0.14f : -0.14f;
	else if (accelerationX > 0) acceleration_x_ = onGround ? 0.14f : 0.14f;

	xVelocity += acceleration_x_ * time_ms;

	xVelocity = xVelocity > 0 ? std::min(xVelocity, X_TARGETSPEED) : std::max(xVelocity, -X_TARGETSPEED);

	float delta = xVelocity * time_ms;

	debugDelta = delta;

	//Going to the right
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, rightCollisionBox(delta));

		if (result.collided) {
			std::cout << "right collided" << std::endl;
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
			std::cout << "left collided" << std::endl;
			xVelocity = 0.0f;
			x_ = result.x + X_BOX.right();
		}
		else {
			x_ += delta;
		}
	}
}

void Player::updateY(uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	float yAcceleration = jumping && yVelocity < 0.0f ? INITIAL_JUMP_VELOCITY : GRAVITY;
	
	yVelocity = std::min(yVelocity + yAcceleration * time_ms, Y_TARGETSPEED);

	//Implies falling
	float delta = yVelocity * time_ms;

	//TODO - Maybe display on screen?
	debugDelta = delta;

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
			std::cout << "top collided" << std::endl;
			y_ = result.y + Y_BOX.height();
			yVelocity = 0.0f;
		}
		else {
			y_ += delta;
			onGround = false;
		}
	}
}

bool Player::testCollision(const BoundingBox& a, const BoundingBox& b) const
{
	if (a.bottom() <= b.top()){
		return false;
	}

	if (a.top() >= b.bottom()){
		return false;
	}

	if (a.right() <= b.left()){
		return false;
	}
	if (a.left() >= b.right()){
		return false;
	}

	//There is a collision if this is reached.
	return true;
}

Player::~Player()
{

}