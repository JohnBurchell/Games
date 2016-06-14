#ifndef ENEMY_STATES
#define ENEMY_STATES

#include "enemy.h"

class FleeState;
class ChaseState;

class IdleState : public State < Enemy >
{

	static IdleState* instance();

	void enter(Enemy* enemy) override;
	void execute(Enemy* enemy) override;
	void exit(Enemy* enemy) override;
};

class ChaseState : public State<Enemy>
{
	static ChaseState* instance();

	void enter(Enemy* enemy) override;
	void execute(Enemy* enemy) override;
	void exit(Enemy* enemy) override;
};

class FleeState : public State<Enemy>
{
	static FleeState* instance();

	void enter(Enemy* enemy) override;
	void execute(Enemy* enemy) override;
	void exit(Enemy* enemy) override;
};

#endif //ENEMY_STATES