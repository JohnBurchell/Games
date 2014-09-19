#ifndef TEST_ENEMY
#define TEST_ENEMY

#include "moveableEntity.h"

class TestEnemy : public MoveableEntity
{
	TestEnemy();

	void update(float time_ms) override;
	void execute() override;
	void draw() override;
};

#endif //TEST_ENEMY