#ifndef STATE_H_
#define STATE_H_

#include "enemy.h"

class TestEnemy;

template<class entity>
class State
{

public:
	virtual void execute(entity*) = 0;
	virtual void enter(entity*) = 0;
	virtual void exit(entity*) = 0;

	virtual ~State() {};
};

#endif //STATE_H_