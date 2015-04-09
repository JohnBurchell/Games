#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#pragma once

#include "graphics.h"

class BoundingBox
{
	public:
		BoundingBox(float x, float y, float width = 32.0f, float height = 32.0f) :
			m_x(x),
			m_y(y),
			m_width(width),
			m_height(height)
		{};

		inline float top()    const { return m_y; };
		inline float bottom() const { return m_y + m_height; };
		inline float left()   const { return m_x; };
		inline float right()  const { return m_x + m_width; };

		inline float width()  const { return m_width; };
		inline float height() const { return m_height; };

		//Potentially viable inline, not sure yet
		inline bool boxCollision(const BoundingBox& a) const 
		{

			if (bottom() <= a.top())
			{
				return false;
			}
			if (top() >= a.bottom())
			{
				return false;
			}
			if (right() <= a.left())
			{
				return false;
			}
			if (left() >= a.right())
			{
				return false;
			}

			//There is a collision if this is reached.
			return true;
		}

		//TODO - Remove me, i am for debugging only.
		void draw(Graphics& graphics, float cameraX, float cameraY, int col = 3) const 
		{ 
			graphics.render_rectanlge(m_x - cameraX, m_y - cameraY, col, static_cast<int>(m_width), static_cast<int>(m_height)); 
		};

	private:
		float m_x, m_y, m_width, m_height;
};

#endif //BOUNDINGBOX_H_