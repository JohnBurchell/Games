#include "TetrisShape.h"

TetrisShape::TetrisShape() :

	filled(false),
	falling(false),
	size(30.f),
	rotation(0),
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

void TetrisShape::changeRotation(const int &newRotation) {
	
	//Set the current rotation of the piece.
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 4; j++) {
			layout[i][j] = layouts[newRotation][i][j];
		}
	}
}

int TetrisShape::getRotation() const {

	return rotation;
}

void TetrisShape::setRotation(const int &_rotation) {

	rotation = _rotation;
}


TetrisShape::~TetrisShape() {}