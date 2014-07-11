#ifndef TetrisShapes_H
#define TetrisShapes_H

#include <vector>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "TetrisShape.h"



class BlankPiece : public TetrisShape 
{

public:
	BlankPiece();
};


class Cube : public TetrisShape 
{

public:
	Cube();

};
class Straight : public TetrisShape 
{

public:	
	Straight();

};

class ZShape : public TetrisShape 
{

public:	
	ZShape();

};

class SShape : public TetrisShape 
{

public:	
	SShape();

};

class TShape : public TetrisShape 
{

public:	
	TShape();

};

class LShape : public TetrisShape 
{

public:	
	LShape();

};

class LShape2 : public TetrisShape 
{

public:	
	LShape2();

};

#endif