#include "enemy.h"
#include "enemyStates.h"

namespace {

	const float CHASE_SPEED = 0.15f;

	BoundingBox Y_BOX = { 10, 2, 12, 30 };
	BoundingBox X_BOX = { 6, 10, 20, 12 };

	const int START_HP = 3;
	const float SPOT_DISTANCE = 200.0f;
}

class TileMap;

Enemy::Enemy(Graphics& graphics, float x, float y) :
	position{ x, y },
	velocityX{ 0.0f },
	health{ START_HP },
	onGround{ false },
	alive{ true },
	targetAquired{ false },
	currentState{ new IdleState }

{
	m_graphics = &graphics;
	if (m_graphics == nullptr)
	{
		throw Graphics::Texture_Error();
	}
	m_sprite.reset(new Animated_Sprite(graphics, "resources/sprites/MyChar.bmp", 0, 0));
}

void Enemy::draw(float cameraX, float cameraY)
{
	//Potential cache miss?
	m_sprite->draw(*m_graphics, position.x - cameraX, position.y - cameraY);
	if(targetAquired)
	{
		m_graphics->renderLine(position.x - cameraX, position.y - cameraY, 
					player.x - cameraX, player.y - cameraY);
	}

}	

std::vector<Enemy::Point> Enemy::bresenham(float x1, float y1, float x2, float y2)
{
	bool steep = (fabs(y2 - y1) > fabs(x2 - x1));

	if (steep)
	{
		std::swap(x1, y1);
		std::swap(x2, y2);
	}

	if (x1 > x2)
	{
		std::swap(x1, x2);
		std::swap(y1, y2);
	}

	const float dx = x2 - x1;
	const float dy = fabs(y2 - y1);

	std::vector<Enemy::Point> points;

	float error = dx / 2.0f;
	const int ystep = (y1 < y2) ? 1 : -1;

	int y = static_cast<int>(y1);

	const int maxX = static_cast<int>(x2);

	for(int x=(int)x1; x<maxX; x++)
  	{
    	if(steep)
    	{
			points.push_back({ y, x });
    	}
    	else
    	{
			points.push_back({ x, y });
    	}
 
    	error -= dy;
    	if(error < 0)
    	{
        	y += ystep;
        	error += dx;
    	}
  	}	

	return points;
}

bool Enemy::isInLineOfSight(std::vector<Point> pixels, TileMap& map)
{
	bool isInLineOfSight = true;

	for(auto& x : pixels)
	{
		if(map.mapTiles[x.y / 32][x.x / 32].type_ == TileMap::TileType::WALL)
		{
			return false;
		}
	}

	return isInLineOfSight;
}

bool Enemy::isInRange(const vector2d& target)
{
	return fabs(position.x + 16 - target.x + 16) <= SPOT_DISTANCE;
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

	m_sprite->update_sprite();

	//TODO - If i optimise the collection of tiles, this won't be that expensive!
	std::vector<BoundingBox> collisionTiles = map.getCollisionTiles();

	if(isInRange(player))
	{
		auto losPixels = bresenham(position.x + 16, position.y + 16, player.x + 16, player.y + 16);
		targetAquired = isInLineOfSight(losPixels, map);
	}
	else
	{
		targetAquired = false;
	}

	updateY(time_ms, collisionTiles);
	updateX(time_ms, collisionTiles);
}

void Enemy::updatePlayerData(float x, float y)
{
	player.x = x;
	player.y = y;
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

void Enemy::stop()
{
	velocityX = 0;
	m_sprite->set_pose(Animated_Sprite::sprite_poses::IDLE);
}

void Enemy::flee()
{
	//Flee to the right
	if (player.x < position.x)
	{
		velocityX = CHASE_SPEED;
		m_sprite->set_facing(Animated_Sprite::sprite_facings::FACING_RIGHT);
		m_sprite->set_pose(Animated_Sprite::sprite_poses::MOVING_RIGHT);
	}
	//Flee to the left
	else if (player.x > position.x) 
	{
		velocityX = -CHASE_SPEED;
		m_sprite->set_facing(Animated_Sprite::sprite_facings::FACING_LEFT);
		m_sprite->set_pose(Animated_Sprite::sprite_poses::MOVING_LEFT);
	}
}

void Enemy::chase()
{
	//Player is to the left of the enemy
	if (player.x < position.x) {
		velocityX = -CHASE_SPEED;

	}
	//Player to the right
	else if (player.x > position.x) {
		velocityX = CHASE_SPEED;
		m_sprite->set_facing(Animated_Sprite::sprite_facings::FACING_RIGHT);
		m_sprite->set_pose(Animated_Sprite::sprite_poses::MOVING_RIGHT);
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
