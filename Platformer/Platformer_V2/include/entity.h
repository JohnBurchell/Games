#ifndef ENTITY_H_
#define ENTITY_H_

#include "common.h"
#include "component.h"
#include <vector>

class Entity
{

public:

	//Consider making this pure virtual so that no-one can make a base object?
	virtual ~Entity() {};
	virtual void update(const double delta) = 0;
	//Move the update out of this class?

private:
	int m_ID;
};

#endif //ENTITY_H_