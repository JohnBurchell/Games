#ifndef BASE_GAME_ENTITY
#define BASE_GAME_ENTITY

#include "common.h"
#include "tileMap.h"

class TileMap;

class BaseGameEntity
{

public:

	virtual ~BaseGameEntity() {};

	virtual void update(uint32_t elapsed_time, TileMap& map) = 0;
	virtual void draw(const float cameraX, const float cameraY) = 0;

};

#endif //BASE_GAME_ENTITY