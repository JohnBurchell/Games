#ifndef TetrisShape_H
#define TetrisShape_H

#include <string>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>

class TetrisShape{

public:

	//Standard constructor
	TetrisShape();

	inline int getX() const { return x; } ;
	inline void setX(const int &_x) { x = _x; };

	float getSize() const;
	void setSize(const float &_Size);

	inline int getY() const {return y; };
	inline void setY(const int &_y) { y = _y; };

	bool isFilled() const;
	void setFilled(const bool &_filled);

	bool isFalling() const;
	void setFalling(const bool &_falling);

	void setRotation(const int &_rotation);
	int getRotation() const;

	void changeRotation(const int &_rotation);

	int layout[4][4];
	//Hold the individual rotations.
	int layouts[4][4][4];
	sf::RectangleShape piece;
	
	~TetrisShape();

private:

	int x, y, rotation;

protected:	

	float size;
	bool filled, falling;

};

#endif