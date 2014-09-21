#include "enemy.h"
#include "enemyStates.h"

namespace {

	constexpr float CHASE_SPEED = 0.15f;

	BoundingBox Y_BOX = { 10, 2, 12, 30 };
	BoundingBox X_BOX = { 6, 10, 20, 12 };

	constexpr int START_HP = 3;
}

class TileMap;

Enemy::Enemy(Graphics& graphics, float x, float y) :
	velocityX{ 0.0f },
	position{ x, y },
	health{ START_HP },
	onGround{ false },
	alive{ true },
	currentState{ new IdleState }

{
	graphics_ = &graphics;
	if (graphics_ == nullptr)
	{
		throw Graphics::Texture_Error();
	}
	sprite_.reset(new Sprite(graphics, "resources/sprites/enemy.bmp", 0, 0, 32, 32));
}

void Enemy::draw(float cameraX, float cameraY)
{
	//Potential cache miss?
	sprite_->draw(*graphics_, position.x - cameraX, position.y - cameraY);
	graphics_->renderLine(position.x - cameraX, position.y - cameraY, playerLocation.playerX - cameraX, playerLocation.playerY - cameraY);
}

bool Enemy::isInLineOfSight(float x1, float y1, float x2, float y2)
{
	//int deltaX = pointB.x - pointA.x;
	//int deltaY = pointB.y - pointA.y;

	bool steep = (fabs(pointB.y - pointA.y) > fabs(pointB.x - pointA.x));

	if (steep)
	{

	}

	if (pointA.x > pointB.x)
	{

	}

	float x0, x1, y0, y1;
	x0 = pointA.x;
	y0 = pointA.y;
	x1 = pointB.x;
	y1 = pointB.y;

	int deltaX = x1 - x0;
	int deltaY = y1 - y0;

	std::vector<Point> points;

	double error = 0;
	double deltaerr = abs(deltaY / deltaX);
	
	int y = y0;
	int ystep = y0 < y1 ? 1 : -1;

	std::cout << deltaX << " | " << deltaY << std::endl;
	std::cout << pointA.x << " | " << pointB.x << std::endl;

	for (int x = x0; x <= x1; ++x)
	{
		points.push_back({ x, y });
		error += deltaY;
		if (2 * error >= deltaX)
		{
			y += ystep;
			error -= deltaX;
		}

	}

	std::cout << points.size() << std::endl;
	return false;
}

void Enemy::changeState(State<Enemy>* newState)
{
	currentState->exit(this);
	currentState = newState;
	currentState->enter(this);
}

void Enemy::update(uint32_t time_ms, TileMap& map)
{
	currentState->execute(this);

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

void Enemy::takeDamage(int damage)
{
	health -= damage;
	if (health <= 0) {
		alive = false;
	}
}

void Enemy::updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	//TODO - Improve, add collision for the enemy
	float yVelocity = 0.0f;

	if (!onGround) {
		yVelocity = 0.55f;
	}

	float delta = yVelocity * time_ms;

	//Going down
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, bottomCollisionBox(delta));

		if (result.collided) {
			position.y = result.y - Y_BOX.bottom();
			yVelocity = 0.0f;
			onGround = true;
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
		}
		else {
			position.y += delta;
			onGround = false;
		}
	}
}

void Enemy::flee()
{
	if (playerLocation.playerX < x_)
	{
		velocityX = CHASE_SPEED;
	}
	else
	{
		velocityX = -CHASE_SPEED;
	}
}

void Enemy::chase()
{
	std::cout << position.length() << std::endl; 

	//Player is to the left of the enemy
	if (playerLocation.playerX < position.x) {
		velocityX = -CHASE_SPEED;
	}
	//Player to the right
	else if (playerLocation.playerX > position.x) {
		velocityX = CHASE_SPEED;
	}
}

void Enemy::seek()
{

}

void Enemy::updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles)
{
	float delta = velocityX * time_ms;

	//Going to the right
	if (delta > 0.0f) {
		auto result = getCollisionResult(collisionTiles, rightCollisionBox(delta));

		if (result.collided) {
			velocityX = 0.0f;
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
			velocityX = 0.0f;
			position.x = result.x + X_BOX.right();
		}
		else {
			position.x += delta;
		}
	}
}

BoundingBox Enemy::leftCollisionBox(float delta) const
{
	return BoundingBox{
		position.x + X_BOX.left() + delta,
		position.y + X_BOX.top(),
		X_BOX.width() / 2 - delta,
		X_BOX.height() };
}

BoundingBox Enemy::rightCollisionBox(float delta) const
{
	return BoundingBox{
		position.x + +X_BOX.left() + X_BOX.width() / 2,
		position.y + X_BOX.top(),
		X_BOX.width() / 2 + delta,
		X_BOX.height() };
}

BoundingBox Enemy::topCollisionBox(float delta) const
{
	return BoundingBox{
		position.x + Y_BOX.left(),
		position.y + Y_BOX.top() + delta,
		Y_BOX.width(),
		Y_BOX.height() / 2 - delta };
}

BoundingBox Enemy::bottomCollisionBox(float delta) const
{
	return BoundingBox{
		position.x + Y_BOX.left(),
		position.y + Y_BOX.top() + Y_BOX.height() / 2,
		Y_BOX.width(),
		Y_BOX.height() / 2 + delta };
}

Enemy::CollisionResult Enemy::getCollisionResult(const std::vector<BoundingBox>& collisionTiles, const BoundingBox& box)
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
	return{ position.x + X_BOX.left(), position.y + Y_BOX.top(), X_BOX.width(), X_BOX.height() };
}


Enemy::~Enemy()
{

}
