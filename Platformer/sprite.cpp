#include "sprite.h"

Sprite::Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width)
{
	texture_ = graphics.loadImage(fileName, true);
	sourceRectangle.x = x;
	sourceRectangle.y = y;
	sourceRectangle.w = width;
	sourceRectangle.h = height;
}

void Sprite::draw(Graphics& graphics, int x, int y)
{
	graphics.renderTexture(texture_, x, y, &sourceRectangle);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture_);
}
