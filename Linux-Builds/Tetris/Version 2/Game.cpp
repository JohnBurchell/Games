#include <SFML/Graphics.hpp>
#include "Game.h"
#include <vector>
#include <chrono>

const int windowHeight = 960, windowWidth = 800;
const int tileSize = 32;

void draw_shape(Tetris_Shape &shape);

Game::Game():
	
	score(0),
	level(0),
	lineCount(0)

	{

	window.create(sf::VideoMode(windowWidth,windowHeight), "Tetris Clone, Version 1");
	window.setFramerateLimit(10);
	window.clear(sf::Color::Black);
	window.display();

	//Setup border:
	left.setPosition(static_cast<float>(windowHeight / tileSize + (tileSize * 2.5f)), static_cast<float>(0));
	left.setSize(sf::Vector2f(tileSize / 2 , windowHeight - (tileSize * 4)));
	left.setFillColor(sf::Color::Blue);

	right.setPosition(static_cast<float>(windowWidth - 160) - (tileSize * 4), static_cast<float>(0));
	right.setSize(sf::Vector2f(tileSize / 2 , windowHeight - (tileSize * 4)));
	right.setFillColor(sf::Color::Blue);

	bottom.setPosition(static_cast<float>((windowWidth - 160) - (tileSize * 16.55f)), static_cast<float>(windowHeight - (tileSize * 4)));
	bottom.setSize(sf::Vector2f(tileSize * 13.05f, tileSize / 2));
	bottom.setFillColor(sf::Color::Blue);
	
	//Creates the box for the next piece
	createBox();

	//Start some UI stuff here!
	gui();

	//Add shapes - Might move this later on.
	//TODO Add rest of the shapes to the container.
	Cube cube;
	Straight straight;
	ZShape zShape;
	LShape lShape;
	LShape2 lShape2;
	TShape TShape;
	SShape sShape;

	//TODO - Maybe have this init done somewhere else?
	shapes.push_back(cube);
	shapes.push_back(straight);
	shapes.push_back(zShape);
	shapes.push_back(lShape);
	shapes.push_back(lShape2);
	shapes.push_back(sShape);
	shapes.push_back(TShape);

	//Set variables up to default values

	boardObj.create_board();
	currShape.falling = false;

}

Game::~Game() {

	delete &boardObj;

}

void Game::run() {

	bool playing = true;
	//Seed 
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << "Running!" << std::endl;

	randomPiece();

	//Add clause to catch if there's a shape above or in the top line.
	while(playing) {

		//If the current shape is empty, it means there's nothing active.
		if(currShape.falling == false) {
			//Get next random piece, assign it to the next piece and set it on the board.
			currShape = nextShape;
			currShape.falling = true;
			randomPiece();
			startTime = clock.getElapsedTime();
		}
		
		if(!emptyTopRow()){
			//TODO - Improve this, especially when adding states.
			std::cout << "GAME OVER!" << std::endl;
			std::cout << "You scored " << score << " points, " <<
				lineCount << " lines and reached level " << level
				<< " Well done!! " << std::endl;
			system("pause");
			exit(0);
		}
		
		input();
		update();
		draw();

	}
}

void Game::draw() {
	drawBoard();
	drawShape();
	drawBorder();
	drawNextShape();
	gui();
	window.display();
}

void Game::drawBoard() {

	for(int i = 0; i < tileSize; i++) {
		for(int j = 0; j < tileSize; j++) {
			if(boardObj.board[i][j].filled) {
				boardObj.board[i][j].piece.setPosition(static_cast<float>(j*tileSize), static_cast<float>(i*tileSize));
				window.draw(boardObj.board[i][j].piece);
			}
		}
	}
}

void Game::update() {
	window.clear(sf::Color::Black);

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		boardObj.moveLeft(currShape);
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		boardObj.moveRight(currShape);	
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		dropPieces();
	}

	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		boardObj.rotatePiece(currShape);
	}

	//If enough time has passed, drop blocks.
	if(dropTimer()){
		dropPieces();
	}

	isWholeLine();
}


void Game::input() {
	/*Handles the input, moving and rotating shpaes when need be.*/

    sf::Event event;
    while(window.pollEvent(event))
    {
		//If cross clicked, exit.
        if(event.type == sf::Event::Closed)
        {
            window.close();
            exit(1);
        }

		//If escape pressed, exit.
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        	exit(1);
    }

}


void Game::drawShape(){

	float floatX, floatY;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(currShape.layout[i][j] > 0){

				//Create proper sizes for the drawing of the shapes.
				floatX = static_cast<float>(currShape.x * tileSize + (j * 32));
				floatY = static_cast<float>(currShape.y * tileSize + (i * 32));

				currShape.piece.setPosition(floatX, floatY);
				window.draw(currShape.piece);
			}
		}
	}
}

void Game::drawNextShape(){

	float floatX, floatY;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(nextShape.layout[i][j] > 0){

				//Create proper sizes for the drawing of the shapes.
				floatX = static_cast<float>((j * 32) + (windowWidth - tileSize * 4));
				floatY = static_cast<float>((i * 32) + tileSize * 2);

				nextShape.piece.setPosition(floatX, floatY);
				window.draw(nextShape.piece);
			}
		}
	}



}

void Game::createBox() {

	box_left.setPosition(windowWidth - (tileSize * 8), tileSize);
	box_left.setSize(sf::Vector2f(tileSize / 2, tileSize * 6));
	box_left.setFillColor(sf::Color::White);

	box_right.setPosition(static_cast<float>(windowWidth - 160) - (tileSize * 4), 5.f);
	box_right.setSize(sf::Vector2f(tileSize / 2, tileSize * 4));
	box_right.setFillColor(sf::Color::White);

	box_bottom.setPosition(static_cast<float>((windowWidth - 160) - (tileSize * 16.55f)), static_cast<float>(windowHeight - (tileSize * 4)));
	box_bottom.setSize(sf::Vector2f(tileSize / 2, tileSize * 4));
	box_bottom.setFillColor(sf::Color::White);

	box_top.setPosition(static_cast<float>((windowWidth - 160) - (tileSize * 16.55f)), static_cast<float>(windowHeight - (tileSize * 4)));
	box_top.setSize(sf::Vector2f(tileSize / 2, tileSize * 4));
	box_top.setFillColor(sf::Color::White);
}

void Game::drawBorder(){

	//Bucket border
	window.draw(left);
	window.draw(right);
	window.draw(bottom);

	//Box border
	//window.draw(box_bottom);
	//window.draw(box_top);
	//window.draw(box_left);
	//window.draw(box_right);

}

/*
	Randomises a piece from the vector or tetris_shape objects
	It sets the piece in the middle of screen (currently at X 7)
*/

void Game::randomPiece(){

	nextShape = shapes[rand() % shapes.size()];
	nextShape.x = 7;
	nextShape.y = 0;
}

bool Game::emptyTopRow(){

	for(int j = 0; j < tileSize / 2; j ++){
		if(boardObj.board[0][j].filled){
			return false;
		}
	}
	return true;
}

void Game::isWholeLine(){
	
	//Sum for calculating a whole line.
	int sum;

	for(int i = 0; i < tileSize; i++){
		sum = 0;
		for(int j = 0; j < tileSize / 2; j++){
			if(boardObj.board[i][j].filled){
				sum++;
			}
		}

		if(sum == 12){
			std::cout << "Whole line!" << std::endl;
			boardObj.clearLine(i);
			score += 10;
			lineCount++;
			//If it's divisible by 5 again, another 5 have been reached so
			//The level goes up.
			if(lineCount % 5 == 0) {
				std::cout << "Level up!" << std::endl;
				level++;
			}
		}
	}
}

void Game::dropPieces() {
	//Move down
	currShape.y++;

	//If bottom or there is a collison, stop, else continue
	if(currShape.y >= 26 || boardObj.isCollision(currShape)) {
		currShape.y--;
		currShape.falling = false;
		boardObj.setPiece(currShape);
	} 
}

bool Game::dropTimer(){


   	sf::Time now = clock.getElapsedTime();
   	sf::Time lifetime = sf::seconds(0.5 - (0.2 * level));


	if(now >= startTime + lifetime){
		startTime = clock.restart();
		return true;
	} 

	return false;
}

void Game::gui() {

	sf::Font font;
	if (!font.loadFromFile("fonts/kenpixel.ttf"))
	{
		std::cerr << " Error loading font!" << std::endl;
		exit(1);
	}

	sf::Text next;
	sf::Text score_text;
	sf::Text lines_text;
	sf::Text level_text;

	//Add to vector of elements
	guiText.push_back(next);
	guiText.push_back(score_text);
	guiText.push_back(lines_text);
	guiText.push_back(level_text);

	std::string text = "";

	next.setFont(font);
	next.setPosition(windowWidth - (tileSize * 8), 80);

	next.setString("Next: ");
	next.setCharacterSize(24);
	next.setColor(sf::Color::White);
	next.setStyle(sf::Text::Bold | sf::Text::Underlined);

	score_text.setFont(font);
	score_text.setPosition(windowWidth - (tileSize * 6), 780);

	text = "Score: " + std::to_string(score);

	score_text.setString(text);
	score_text.setCharacterSize(24); 
	score_text.setColor(sf::Color::White);
	score_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	level_text.setFont(font);
	level_text.setPosition(windowWidth - (tileSize * 6), 580);
	
	text = "Level: " + std::to_string(level);
	level_text.setString(text);
	level_text.setCharacterSize(24);
	level_text.setColor(sf::Color::White);
	level_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	lines_text.setFont(font); 
	lines_text.setPosition(windowWidth - (tileSize * 6), 680);

	text = "Lines: " + std::to_string(lineCount);
	lines_text.setString(text);
	lines_text.setCharacterSize(24);
	lines_text.setColor(sf::Color::White);
	lines_text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	window.draw(next);
	window.draw(level_text);
	window.draw(score_text);
	window.draw(lines_text);

}

void Game::updateGui() {

	std::string text = "Score: " + std::to_string(score);
	guiText[1].setString(text);

	text = "Level: " + std::to_string(level);
	guiText[2].setString(text);

	text = "Lines: " + std::to_string(lineCount);
	guiText[3].setString(text);

	std::vector<sf::Text>::iterator it;

	for(it = guiText.begin(); it != guiText.end(); it++)
	{
		window.draw(*it);
	}
}


