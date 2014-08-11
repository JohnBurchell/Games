#ifndef BOUNDINGBOX_H_
#define BONUDINGBOX_H_
#pragma once

#include "graphics.h"

class BoundingBox
{
	public:
		BoundingBox(int x, int y, int width, int height) :
			x_(x),
			y_(y),
			width_(width),
			height_(height)
		{};

		inline int top()    const { return y_; };
		inline int bottom() const { return y_ + height_; };
		inline int left()   const { return x_; };
		inline int right()  const { return x_ + width_; };

		inline int width()  const { return width_; };
		inline int height() const { return height_; };

		void draw(Graphics& graphics, int cameraX, int cameraY) const { graphics.render_rectanlge(x_ - cameraX, y_ - cameraY, 3, width_, height_); };

	private:
		const int x_, y_, width_, height_;
};

#endif //BOUNDINGBOX_H_