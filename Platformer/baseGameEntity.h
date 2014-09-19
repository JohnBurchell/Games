#ifndef BASE_GAME_ENTITY
#define BASE_GAME_ENTITY

class BaseGameEntity
{

public:

	virtual ~BaseGameEntity() {};

	virtual void update(float elapsed_time) = 0;
	virtual void draw() = 0;

};

#endif //BASE_GAME_ENTITY