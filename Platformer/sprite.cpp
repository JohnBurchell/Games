#include "sprite.h"

Sprite::Sprite(Graphics& graphics, std::string fileName, float x, float y, int height, int width)
{
	m_texture = graphics.loadImage(fileName, true);
	m_source_rectangle.x = static_cast<int>(x);
	m_source_rectangle.y = static_cast<int>(y);
	m_source_rectangle.w = width;
	m_source_rectangle.h = height;
}

void Sprite::draw(Graphics& graphics, float x, float y)
{
	graphics.renderTexture(m_texture, x, y, &m_source_rectangle);
}

