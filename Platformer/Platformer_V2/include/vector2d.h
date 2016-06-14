#ifndef VECTOR2D
#define VECTOR2D

#include <cmath>

class vector2d
{
public:

	vector2d() :
		x{ 0 },
		y{ 0 } {};
	vector2d(float x, float y) :
		x{ x },
		y{ y } {};

	float x, y;

	//Reset the vector to zero
	inline void zero() { x = 0; y = 0; };

	//Some standard vector operations
	inline float length() const;
	inline void normalise();
	
};

float vector2d::length() const
{
	return sqrt(x * x + y * y);
}

void vector2d::normalise()
{
	//ok
}
#endif //VECTOR2D