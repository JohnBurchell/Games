#ifndef COMPONENT_H_
#define COMPONENT_H_

#include <vector>

class Component
{

public:
	virtual ~Component();
	virtual void receive_message(int message) = 0;
};

#endif //COMPONENT_H_