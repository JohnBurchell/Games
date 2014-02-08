#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>

const int windowHeight = 800, windowWidth = 600;
const int tileSize = 32;

void draw_shape(Tetris_Shape &shape);

Game::Game(){

	window.create(sf::VideoMode(windowWidth,windowHeight), "Tetris Clone, Version 1");
	window.setFramerateLimit(5);
	window.clear(sf::Color::Black);
	window.display();

	//Add shapes - Might move this later on.
	//TODO Add rest of the shapes to the container.
	Cube cube;
	Straight straight;
	ZShape zShape;

	//TODO - Maybe have this init done somewhere else?
	std::vector<Tetris_Shape> shapes;
	shapes.push_back(cube);
	shapes.push_back(straight);
	shapes.push_back(zShape);


	boardObj.create_board();
}

void Game::Run() {

	bool playing = true;

	std::cout << "Running!" << std::endl;

	Cube cube;
	Straight straight;
	ZShape zShape;
	draw_shape(zShape);

	boardObj.setPiece(zShape);

	while(playing) {
		Input();
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
			if(boardObj.board[i][j].filled) {
				boardObj.board[i][j].piece.setPosition(j*tileSize, i*tileSize);
				window.draw(boardObj.board[i][j].piece);
			}
		}
	}
}

void Game::Update() {
	window.clear(sf::Color::Black);
	boardObj.updateBoard();
	boardObj.dropPieces();
}


void Game::Input() {
	/*Handles the input, moving and rotating shpaes when need be.*/

    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
            exit(1);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        	exit(1);
    }
}


void draw_shape(Tetris_Shape &shape){

	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			std::cout << shape.layout[i][j];
		}

		std::cout << " " << std::endl;
	}

}