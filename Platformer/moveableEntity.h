#ifndef MOVEABLE_ENTITY_H_
#define MOVEABLE_ENTITY_H_

#include "baseGameEntity.h"
#include "graphics.h"
#include "sprite.h"
#include "common.h"

class Graphics;
class Sprite;

class MoveableEntity : public BaseGameEntity
{
public:
	MoveableEntity() {};
	~MoveableEntity() {};

//Why protected?
protected:

	Graphics* graphics;
	std::unique_ptr<Sprite> sprite_;
};

#endif //MOVEABLE_ENTITY_H_