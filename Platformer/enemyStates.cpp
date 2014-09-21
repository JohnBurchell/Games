#include "enemyStates.h"
#include "state.h"
#include "enemy.h"

class Enemy;

IdleState* IdleState::instance()
{
	static IdleState idle;

	return &idle;
}

void IdleState::enter(Enemy* enemy)
{
	std::cout << "Becoming idle!" << std::endl;
}

void IdleState::execute(Enemy* enemy)
{
	if (enemy->isAlive() && enemy->getHealth() < 3)
	{
		enemy->changeState(new ChaseState);
	}
}

void IdleState::exit(Enemy* enemy)
{
	std::cout << "Stopping being idle!" << std::endl;
}

ChaseState* ChaseState::instance()
{
	static ChaseState idle;

	return &idle;
}

void ChaseState::enter(Enemy* enemy)
{
	std::cout << "Starting the chase!" << std::endl;
}

void ChaseState::execute(Enemy* enemy)
{
	enemy->chase();
	if (enemy->getHealth() == 1)
	{
		enemy->changeState(new FleeState);
	}
}

void ChaseState::exit(Enemy* enemy)
{
	std::cout << "Stopping the chase" << std::endl;
}

FleeState* FleeState::instance()
{
	static FleeState idle;

	return &idle;
}

void FleeState::enter(Enemy* enemy)
{
	std::cout << "Becoming scared.." << std::endl;
}

void FleeState::execute(Enemy* enemy)
{
	std::cout << "RUN AWAY!!!!!" << std::endl;

	enemy->flee();
}

void FleeState::exit(Enemy* enemy)
{
	std::cout << "Calming down..." << std::endl;
}