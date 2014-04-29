#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "tetris_shapes.h"
#include <string>

BlankPiece::BlankPiece(){

	piece.setFillColor(sf::Color::Black);
	piece.setSize(sf::Vector2f(size, size));
	filled = false;

}

Cube::Cube(){

	//Maroon
	piece.setFillColor(sf::Color (128, 0, 0));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;


	layout[0][0] = 1;
	layout[0][1] = 1;
	layout[1][0] = 1;
	layout[1][1] = 1;

	//Cube now looks like
	//1, 1, 0, 0
	//1, 1, 0, 0
	//0, 0, 0, 0
	//0, 0, 0, 0


}

Straight::Straight() {

	//Orange
	piece.setFillColor(sf::Color (236,88,0));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

	//Normal:
	//0, 0, 0, 0
	//1, 1, 1, 1
	//0, 0, 0, 0
	//0, 0, 0, 0
	//layout[1][0] = 1;
	//layout[1][1] = 1;
	//layout[1][2] = 1;
	//layout[1][3] = 1;

	//Rotation 2:
	//0, 0, 1, 0
	//0, 0, 1, 0
	//0, 0, 1, 0
	//0, 0, 1, 0
	layout[0][2] = 1;
	layout[1][2] = 1;
	layout[2][2] = 1;
	layout[3][2] = 1;

	//Rotation 3:
	//0, 1, 0, 0
	//0, 1, 0, 0
	//0, 1, 0, 0
	//0, 1, 0, 0
	//layout[0][1] = 1;
	//layout[1][1] = 1;
	//layout[2][1] = 1;
	//layout[3][1] = 1;

	//Rotation 4:
	//0, 0, 0, 0
	//0, 0, 0, 0
	//1, 1, 1, 1
	//0, 0, 0, 0
	//layout[2][0] = 1;
	//layout[2][1] = 1;
	//layout[2][2] = 1;
	//layout[2][3] = 1;

}

ZShape::ZShape() {

	piece.setFillColor(sf::Color::Green);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

	//Normal:
	//1, 1, 0, 0
	//0, 2, 1, 0
	//0, 0, 0, 0
	//0, 0, 0, 0

	//Pivot anchor is at 2.
	layout[0][0] = 1;
	layout[0][1] = 1;
	layout[1][1] = 2;
	layout[1][2] = 1;

}

SShape::SShape() {

	piece.setFillColor(sf::Color (8, 232, 222));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;
	
	//Normal:
	//0, 1, 1, 0
	//2, 1, 0, 0
	//0, 0, 0, 0
	//0, 0, 0, 0

	//Pivot anchor is at 2.
	layout[0][1] = 1;
	layout[0][2] = 1;
	layout[1][0] = 2;
	layout[1][1] = 1;

}

TShape::TShape() {

	piece.setFillColor(sf::Color::Yellow);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;
	
	//Normal:
	//0, 1, 0, 0
	//1, 2, 1, 0
	//0, 0, 0, 0
	//0, 0, 0, 0

	//Pivot anchor is at 2.
	layout[0][1] = 1;
	layout[1][0] = 1;
	layout[1][1] = 2;
	layout[1][2] = 1;

}

LShape::LShape() {

	//Azure blue
	piece.setFillColor(sf::Color (0, 102, 255));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;
	
	//Normal:
	//1, 0, 0, 0
	//1, 2, 1, 0
	//0, 0, 0, 0
	//0, 0, 0, 0

	//Pivot anchor is at 2.
	layout[0][0] = 1;
	layout[1][0] = 1;
	layout[1][1] = 1;
	layout[1][2] = 1;


}

LShape2::LShape2() {

	//Indigo
	piece.setFillColor(sf::Color (75, 0, 130));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;
	
	//Normal:
	//0, 0, 1, 0
	//1, 2, 1, 0
	//0, 0, 0, 0
	//0, 0, 0, 0

	//Pivot anchor is at 2.
	layout[0][2] = 1;
	layout[1][0] = 1;
	layout[1][1] = 1;
	layout[1][2] = 1;

}
