#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

#include "main.h"
#include "shapes.h"

const int windowHeight = 800, windowWidth = 600;
const int tileSize = 16;


int main(int argc, char *argv[]){

	Game game;
	game.run();
}

Game::Game(){

	window.create(sf::VideoMode(windowWidth,windowHeight), "Tetris Clone, Version 2");
	window.setFramerateLimit(5);
	window.clear(sf::Color::Black);
	window.display();
	board.createBoard();
}

void Game::run() {

	std::cout << "Running!" << std::endl;
	playing = true;
	printBoard();


	while(playing) {
		input();
		draw();
		update();
	}
}

void Game::draw() {
	window.display();
}

void Game::update() {
	window.clear(sf::Color::Black);
}

void Game::input() {

    sf::Event event;
    while(window.pollEvent(event))
    {
        if(event.type == sf::Event::Closed)
        {
            window.close();
            exit(1);
        }

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
        	playing = false;
        	exit(1);
        }

    }
}

void Game::printBoard(){

	for(int i = 0; i < 20; i++){
		for(int j = 0; j < 16; j++){
			std::cout << board.board[i][j];
		}

		std::cout << " " << std::endl;
	}
}