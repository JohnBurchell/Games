#ifndef MOVEABLE_ENTITY_H_
#define MOVEABLE_ENTITY_H_

#include "entity.h"
#include "common.h"

class Graphics;
class Animated_Sprite;

class Moveable_Entity : public Entity
{
public:
	Moveable_Entity() {};
	~Moveable_Entity() {};

private:

	//Graphics* m_graphics;
	//std::unique_ptr<Animated_Sprite> m_sprite;
};

#endif //MOVEABLE_ENTITY_H_