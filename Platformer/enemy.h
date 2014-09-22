#ifndef TEST_ENEMY
#define TEST_ENEMY

#include "common.h"
#include "moveableEntity.h"
#include "state.h"
#include "boundingBox.h"

class TileMap;

class Enemy : public MoveableEntity
{
public:
	Enemy(Graphics& graphics, float x, float y);
	~Enemy();

	void update(uint32_t time_ms, TileMap& map) override;
	void draw(float cameraX, float cameraY) override;

	void changeState(State<Enemy>* test);
	void revertToPreviousState();

	inline bool isAlive() { return alive; };
	inline int getHealth() { return health; };
	void takeDamage(int damage = 1);

	inline const vector2d getPosition() const { return position; };

	struct Point
	{
		int x, y;
	};

	inline bool isTargetAquired() { return targetAquired; };

	bool isInRange(const vector2d& target);

	void stop();
	void flee();
	void seek();
	void chase();
	void wander();

	void updatePlayerData(float x, float y);
	BoundingBox getDamageRectangle();

private:

	vector2d position;
	vector2d Target;
	vector2d player;

	float velocityX;
	int health;
	bool onGround, alive, targetAquired;

	State<Enemy>* currentState;
	State<Enemy>* previousState;
	State<Enemy>* globalState;

	void updateY(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);
	void updateX(const uint32_t time_ms, std::vector<BoundingBox>& collisionTiles);

	std::vector<Point> bresenham(float x1, float y1, float x2, float y2);
	bool isInLineOfSight(std::vector<Point> pixels, TileMap& map);

	struct CollisionResult
	{
		float x, y;
		bool collided;
	};

	BoundingBox rightCollisionBox(float delta) const;
	BoundingBox leftCollisionBox(float delta) const;
	BoundingBox topCollisionBox(float delta) const;
	BoundingBox bottomCollisionBox(float delta) const;

	CollisionResult getCollisionResult(const std::vector<BoundingBox>& collidingTiles, const BoundingBox& box);

};

#endif //TEST_ENEMY