#include "TetrisShape.h"

TetrisShape::TetrisShape() :

	filled(false),
	falling(false),
	layout(4, std::vector<int>(4)),
	size(30.f),
	x(0),
	y(0)

{}

bool TetrisShape::isFilled() const 
{
	return filled;
}

void TetrisShape::setFilled(const bool &_filled)
{
	filled = _filled;
}

float TetrisShape::getSize() const
{
	return size;
}

void TetrisShape::setSize(const float &_size)
{
	size = _size;
}

bool TetrisShape::isFalling() const
{
	return falling;
}

void TetrisShape::setFalling(const bool &_falling)
{
	falling = _falling;
}


TetrisShape::~TetrisShape() {}