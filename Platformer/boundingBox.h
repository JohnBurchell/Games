#ifndef BOUNDINGBOX_H_
#define BONUDINGBOX_H_
#pragma once

#include "graphics.h"

class BoundingBox
{
	public:
		BoundingBox(float x, float y, float width = 32, float height = 32) :
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


		//TODO - Remove me, i am for debugging only.
		void draw(Graphics& graphics, int cameraX, int cameraY, int col = 3) const { graphics.render_rectanlge(static_cast<int>(x_ - cameraX), static_cast<int>(y_ - cameraY), col, static_cast<int>(width_), static_cast<int>(height_)); };

	private:
		const float x_, y_, width_, height_;
};

#endif //BOUNDINGBOX_H_