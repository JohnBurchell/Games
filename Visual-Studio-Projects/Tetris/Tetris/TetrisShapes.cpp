#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <array>
#include "TetrisShapes.h"
#include <string>

BlankPiece::BlankPiece()
{

	piece.setFillColor(sf::Color::Black);
	piece.setSize(sf::Vector2f(size, size));
	filled = false;

}

Cube::Cube()
{

	//Maroon
	piece.setFillColor(sf::Color (128, 0, 0));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

Straight::Straight() 
{

	//Orange
	piece.setFillColor(sf::Color (236,88,0));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

ZShape::ZShape() 
{

	piece.setFillColor(sf::Color::Green);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

SShape::SShape() 
{

	piece.setFillColor(sf::Color (8, 232, 222));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

TShape::TShape() 
{

	piece.setFillColor(sf::Color::Yellow);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

LShape::LShape() 
{

	//Azure blue
	piece.setFillColor(sf::Color (0, 102, 255));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}

LShape2::LShape2()
{

	//Indigo
	piece.setFillColor(sf::Color (75, 0, 130));
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

}
