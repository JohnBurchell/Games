#include "background.h"
#include "sprite.h"

class Sprite;

Background::Background(Graphics& graphics, std::string filename, bool transparency)
{
	texture = graphics.loadImage(filename, transparency);
}

void Background::draw(Graphics& graphics, float x, float y)
{
	graphics.renderTexture(texture, x, y);
}

Background::~Background()
{
	SDL_DestroyTexture(texture);
}