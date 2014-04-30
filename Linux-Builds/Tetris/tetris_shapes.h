//This will define all the shapes.

#include "tetris_shape.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>

class BlankPiece : public Tetris_Shape {

public:
	BlankPiece();
};


class Cube : public Tetris_Shape {

public:
	Cube();

};
class Straight : public Tetris_Shape {

public:	
	Straight();

};

class ZShape : public Tetris_Shape {

public:	
	ZShape();

};
