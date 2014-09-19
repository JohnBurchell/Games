#ifndef TEST_ENEMY
#define TEST_ENEMY

#include "moveableEntity.h"

class TestEnemy : public MoveableEntity
{
public:
	TestEnemy(Graphics& graphics);

	void update(float time_ms) override;
	void draw() override;
};

#endif //TEST_ENEMY