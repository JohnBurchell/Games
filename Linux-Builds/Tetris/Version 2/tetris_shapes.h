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

class SShape : public Tetris_Shape {

public:	
	SShape();

};

class TShape : public Tetris_Shape {

public:	
	TShape();

};

class LShape : public Tetris_Shape {

public:	
	LShape();

};

class LShape2 : public Tetris_Shape {

public:	
	LShape2();

};