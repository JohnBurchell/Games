#include "component.h"

#include <SDL.h>

class Visual : public Component
{
	//Provides the texture and clipping boxes for the visual compliment to an entity.
	SDL_Texture* texture;
	SDL_Rect clipping_rect;
};