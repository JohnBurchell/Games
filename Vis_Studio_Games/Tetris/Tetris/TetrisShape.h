#ifndef TetrisShape_H
#define TetrisShape_H

#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

class TetrisShape{

public:

	//Standard constructor
	TetrisShape();

	inline int getX() { return x; };
	inline void setX(const int &_x) { x = _x; };

	float getSize();
	void setSize(const float &_Size);

	inline int getY() {return y; };
	inline void setY(const int &_y) { y = _y; };

	bool isFilled();
	void setFilled(const bool &_filled);

	bool isFalling();
	void setFalling(const bool &_falling);

	std::vector< std::vector<int> > layout;
	sf::RectangleShape piece;

	~TetrisShape();

private:

	int x, y;

protected:	

	float size;
	bool filled, falling;

};

#endif