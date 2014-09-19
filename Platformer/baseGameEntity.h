#ifndef BASE_GAME_ENTITY
#define BASE_GAME_ENTITY

template<entity_type*>
class BaseGameEntity
{

public:

	virtual ~BaseGameEntity() {};

	virtual void execute();
	virtual void update(float elapsed_time);
	virtual void draw();

};

#endif //BASE_GAME_ENTITY