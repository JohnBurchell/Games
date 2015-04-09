#ifndef MOVEABLE_ENTITY_H_
#define MOVEABLE_ENTITY_H_

#include "baseGameEntity.h"
#include "graphics.h"
#include "animated_sprite.h"
#include "common.h"


class MoveableEntity : public BaseGameEntity
{
public:
	MoveableEntity() {};
	~MoveableEntity() {};

protected:

	Graphics* m_graphics;
	std::unique_ptr<Animated_Sprite> m_sprite;
};

#endif //MOVEABLE_ENTITY_H_