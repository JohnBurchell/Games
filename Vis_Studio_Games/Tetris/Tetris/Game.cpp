#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

const int windowHeight = 800, windowWidth = 600;
const int tileSize = 32;

Game::Game(){

	window.create(sf::VideoMode(windowWidth,windowHeight), "Tetris Clone, Version 1");
	window.setFramerateLimit(10);
	window.clear(sf::Color::Black);
	window.display();

	//Add shapes - Might move this later on.
	//TODO Add rest of the shapes to the container.
	Cube cube;
	Straight straight;

	std::vector<Tetris_Shape> shapes;
	shapes.push_back(cube);
	shapes.push_back(straight);

	boardObj.create_board2();
}

void Game::Run() {

	bool playing = true;

	std::cout << "Running!" << std::endl;

	Cube cube;
	Straight straight;
	boardObj.setPiece(cube);

	while(playing) {
		Draw();
		Update();
	}
}

void Game::Draw() {
	DrawBoard();
	window.display();
}

void Game::DrawBoard() {

	for(int i = 0; i < 16; i++) {
		for(int j = 0; j < 16; j++) {
			if(boardObj.board2[i][j].filled) {
				boardObj.board2[i][j].piece.setPosition(j*tileSize, i*tileSize);
				window.draw(boardObj.board2[i][j].piece);
			}
		}
	}
}

void Game::Update() {
	window.clear(sf::Color::Black);
	DropPieces();
}

void Game::DropPieces() {

	BlankPiece blank;
	for(int i = 14; i >= 0; i--) {
		for(int j = 15; j >= 0; j--) {
			if(boardObj.board2[i][j].filled && boardObj.board2[i][j].isFalling) {
				boardObj.board2[i+1][j] = boardObj.board2[i][j];
				boardObj.board2[i][j] = blank;
			}
			if(boardObj.board2[i][j].filled && !boardObj.board2[i][j].isFalling)
				std::cout << "i am a stopped brick" << std::endl;
		}
	}
}

void Game::StopShape(Tetris_Shape &shape) {
	//TODO - Make it so that it searches or finds the shape parts and stops them from falling.
}
