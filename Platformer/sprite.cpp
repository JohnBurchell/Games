#include "sprite.h"

Sprite::Sprite(Graphics& graphics, std::string fileName, int x, int y, int height, int width)
{
	m_texture = graphics.loadImage(fileName, true);
	m_source_rectangle.x = x;
	m_source_rectangle.y = y;
	m_source_rectangle.w = width;
	m_source_rectangle.h = height;
}

void Sprite::draw(Graphics& graphics, float x, float y)
{
	//TODO - this needs to change, possible loss of precision.
	graphics.renderTexture(m_texture, static_cast<int>(x), static_cast<int>(y), &m_source_rectangle);
}

