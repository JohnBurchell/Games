#include "player.h"
#include <algorithm>
#include <assert.h>

using std::vector;

//Gravity = 2 * max jump height / time to apex

//Initial jump velocity = 2 * gravity * height at max jump

namespace {

	const float INITIAL_JUMP_VELOCITY = 0.35f;
	const float GRAVITY = 0.00089f;
	const float MAX_Y_SPEED = 0.5f;
	const float JUMP_GRAVITY = 0.00065f;
	const float X_TARGETSPEED = 0.24f;

	//The boxes should be a little bit bigger than the player sprite
	BoundingBox Y_BOX = { 10, 2, 12, 30 };
	BoundingBox X_BOX = { 6, 10, 20, 12 };
}

Player::Player(Graphics& graphics, float x, float y) :

	position{ x, y },
	xVelocity{ 0.0f },
	yVelocity{ 0.0f },
	accelerationX{ 0 },
	health{ 10 },
	jumping{ false },
	invulnerable{ false },
	invulnTime{ 300.0f },
	debugDelta{ 0.0f },
	debug{ false }

{
	sprite.reset(new Animated_Sprite(graphics, "resources/sprites/MyChar.bmp", 0, 0));
}

void Player::draw(Graphics& graphics, float cameraX, float cameraY)
{
	sprite->draw(graphics, position.x - cameraX, position.y - cameraY);

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

		BoundingBox y = { position.x + Y_BOX.left(), position.y + Y_BOX.top(), Y_BOX.width(), Y_BOX.height() };
		BoundingBox x = { position.x + X_BOX.left(), position.y + X_BOX.top(), X_BOX.width(), X_BOX.height() };
		y.draw(graphics, cameraX, cameraY, 2);
		x.draw(graphics, cameraX, cameraY, 2);
		//Damage rectangle below.
		//getDamageRectangle().draw(graphics, cameraX, cameraY, 5);
	}
}

void Player::enableDebug()
{
	debug = !debug;
}

void Player::startJump()
{
	if (onGround && !jumping) {
		yVelocity = -INITIAL_JUMP_VELOCITY;
		jumping = true;
	}
}

void Player::shoot()
{
	//Animation, sound?
	//Return where the bullet should spawn and in what direction it is travelling with the velocity
	/*
		Return -1 for shooting to the left
		Return 1 for shooting to the right
		Return the position of the "gun barrel", at the moment this will be 16 up from the bottom of the sprite
		Return the velocity of the shot 
	*/
	std::cout << "Fire!" << std::endl;

	if (sprite->get_facing() == Animated_Sprite::sprite_facings::FACING_LEFT)
	{
		//Negative velocity if not already
	}
	else if (sprite->get_facing() == Animated_Sprite::sprite_facings::FACING_RIGHT)
	{
		//Positive velocity if not already
	}
}

void Player::startMovingRight()
{
	accelerationX = 1;
	sprite->set_facing(Animated_Sprite::sprite_facings::FACING_RIGHT);
	sprite->set_pose(Animated_Sprite::sprite_poses::MOVING_RIGHT);
}

void Player::startMovingLeft()
{
	accelerationX = -1;
	sprite->set_facing(Animated_Sprite::sprite_facings::FACING_LEFT);
	sprite->set_pose(Animated_Sprite::sprite_poses::MOVING_LEFT);
}

void Player::stopMoving()
{
	accelerationX = 0;
	xVelocity = 0;
	sprite->set_pose(Animated_Sprite::sprite_poses::IDLE);
}

void Player::update(uint32_t time_ms, TileMap& map)
{
	std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	if (debug) {
		//debugTiles = map.getCollisionTilesTest(bottomCollisionBox(10));
		//No copy constructor exists for collision tiles yet - TODO?
		debugTiles = map.getCollisionTiles();
	}

	updateY(time_ms, collisionTiles);
	updateX(time_ms, collisionTiles);
	sprite->update_sprite();

	if(invulnerable && invulnTime > 0.0f)
	{
		invulnTime -= time_ms;
	}
	else
	{
		invulnerable = false;
	}
}

BoundingBox Player::leftCollisionBox(float delta) const
{
	return BoundingBox{ 
		position.x + X_BOX.left() + delta,
		position.y + X_BOX.top(),
		X_BOX.width() / 2 - delta, 
		X_BOX.height() };
}

BoundingBox Player::rightCollisionBox(float delta) const
{
	return BoundingBox{ 
		position.x + +X_BOX.left() + X_BOX.width() / 2,
		position.y + X_BOX.top(),
		X_BOX.width() / 2 + delta, 
		X_BOX.height()};
}

BoundingBox Player::topCollisionBox(float delta) const
{
	return BoundingBox{ 
		position.x + Y_BOX.left(),
		position.y + Y_BOX.top() + delta,
		Y_BOX.width(), 
		Y_BOX.height() / 2 - delta};
}

BoundingBox Player::bottomCollisionBox(float delta) const
{
	return BoundingBox{ 
		position.x + Y_BOX.left(),
		position.y + Y_BOX.top() + Y_BOX.height() / 2,
		Y_BOX.width(),
		Y_BOX.height() / 2 + delta};
}

Player::CollisionResult Player::getCollisionResult(std::vector<BoundingBox>& collisionTiles, const BoundingBox& box)
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

BoundingBox Player::getDamageRectangle()
{
	return{ position.x + X_BOX.left(), position.y + Y_BOX.top(), X_BOX.width(), Y_BOX.height() };
}

void Player::takeDamage()
{
	if(health <= 0 && !invulnerable)
	{
		std::cout << "Dead" << std::endl;
	}
	else if(!invulnerable)
	{	
		health -= 1;
		//Take damage
		//Knockback? Away?
		//Flash?
		invulnerable = true;
		invulnTime = 300.0f;
	}
	else 
	{
		//Do nothing, maybe some update?
		std::cout << "CAN'T TOUCH THIS" << std::endl;
	}
}

void Player::updateX(uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	// Euler Integration
	//position += velocity * deltaTime
	//velocity += acceleration * deltaTime
	float acceleration_x_ = 0.0f;

	if (accelerationX < 0) acceleration_x_ = onGround ? -X_TARGETSPEED : -X_TARGETSPEED;
	else if (accelerationX > 0) acceleration_x_ = onGround ? X_TARGETSPEED : X_TARGETSPEED;

	xVelocity += acceleration_x_ * time_ms;

	xVelocity = xVelocity > 0 ? std::min(xVelocity, X_TARGETSPEED) : std::max(xVelocity, -X_TARGETSPEED);

	float delta = xVelocity * time_ms;

	debugDelta = delta;

	//Going to the right
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, rightCollisionBox(delta));

		if (result.collided) {
			xVelocity = 0.0f;
			position.x = result.x - X_BOX.right();
		}
		else {
			position.x += delta;
		}
	}
	//Going left
	else {
		auto result = getCollisionResult(collisionTiles, leftCollisionBox(delta));

		if (result.collided) {
			xVelocity = 0.0f;
			position.x = result.x + X_BOX.right();
		}
		else {
			position.x += delta;
		}
	}
}

void Player::updateY(uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	float yAcceleration = jumping && yVelocity < 0.0f ? GRAVITY : JUMP_GRAVITY;
	
	yVelocity = std::min(yVelocity + yAcceleration * time_ms, MAX_Y_SPEED);

	float delta = yVelocity * time_ms;

	debugDelta = delta;

	//Going down
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, bottomCollisionBox(delta));

		if (result.collided) {
			position.y = result.y - Y_BOX.bottom();
			yVelocity = 0.0f;
			onGround = true;
			jumping = false;
		}
		else {
			position.y += delta;
			onGround = false;
		}
	}
	//Going up
	else {
		auto result = getCollisionResult(collisionTiles, topCollisionBox(delta));

		if (result.collided) {
			position.y = result.y + Y_BOX.height();
			yVelocity = 0.0f;
			onGround = true;
		}
		else {
			position.y += delta;
			onGround = false;
		}
	}
}

Player::~Player()
{

}