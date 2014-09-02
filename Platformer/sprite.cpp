#include "sprite.h"

Sprite::Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width)
{
	texture_ = graphics.loadImage(fileName, true);
	sourceRectangle.x = x;
	sourceRectangle.y = y;
	sourceRectangle.w = width;
	sourceRectangle.h = height;
}

void Sprite::draw(Graphics& graphics, float x, float y)
{
	graphics.renderTexture(texture_, static_cast<int>(x), static_cast<int>(y), &sourceRectangle);
}

Sprite::~Sprite()
{
	SDL_DestroyTexture(texture_);
}
