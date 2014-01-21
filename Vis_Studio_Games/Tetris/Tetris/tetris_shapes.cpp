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

	piece.setFillColor(sf::Color::Red);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

	layout[0][0] = 0;
	layout[0][1] = 0;
	layout[1][0] = 0;
	layout[1][1] = 0;
	layout[2][0] = 1;
	layout[2][1] = 1;
	layout[3][0] = 1;
	layout[3][1] = 1;

	//Cube now looks like
	//0, 0
	//0, 0
	//1, 1
	//1, 1

}

Straight::Straight() {

	piece.setFillColor(sf::Color::Yellow);
	piece.setSize(sf::Vector2f(size, size));
	filled = true;

	layout[0][0] = 1;
	layout[0][1] = 0;
	layout[1][0] = 1;
	layout[1][1] = 0;
	layout[2][0] = 1;
	layout[2][1] = 0;
	layout[3][0] = 1;
	layout[3][1] = 0;
}