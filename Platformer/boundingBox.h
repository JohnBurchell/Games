#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_
#pragma once

#include "graphics.h"

class BoundingBox
{
	public:
		BoundingBox(float x, float y, float width = 32.0f, float height = 32.0f) :
			x_(x),
			y_(y),
			width_(width),
			height_(height)
		{};

		inline float top()    const { return y_; };
		inline float bottom() const { return y_ + height_; };
		inline float left()   const { return x_; };
		inline float right()  const { return x_ + width_; };

		inline float width()  const { return width_; };
		inline float height() const { return height_; };

		//Potentially viable inline, not sure yet
		inline bool boxCollision(const BoundingBox& a) const {

			if (bottom() <= a.top()){
				return false;
			}
			if (top() >= a.bottom()){
				return false;
			}
			if (right() <= a.left()){
				return false;
			}
			if (left() >= a.right()){
				return false;
			}

			//There is a collision if this is reached.
			return true;
		}

		//TODO - Remove me, i am for debugging only.
		//void draw(Graphics& graphics, float cameraX, float cameraY, int col = 3) const { graphics.render_rectanlge(x_ - cameraX, y_ - cameraY, col, width_, height_); };

	private:
		float x_, y_, width_, height_;
};

#endif //BOUNDINGBOX_H_