#include <SFML/Graphics.hpp>
#include "Game.h"

const int windowHeight = 960, windowWidth = 800;
const int tileSize = 32;

using namespace std::chrono;

Game::Game():
	
	score(0),
	level(1),
	lineCount(0)

	{}

Game::~Game() {}

void Game::setup() {

	window.create(sf::VideoMode(windowWidth,windowHeight), "Tetris Clone, Version 1");
	window.clear(sf::Color::Black);
	window.display();

	//Setup border - Using static_cast to avoid compiler warnings
	left.setPosition(static_cast<float>(windowHeight / tileSize + (tileSize * 2.5f)), static_cast<float>(0));
	left.setSize(sf::Vector2f(tileSize / 2 , windowHeight - (tileSize * 4)));
	left.setFillColor(sf::Color::Blue);

	right.setPosition(static_cast<float>(windowWidth - 160) - (tileSize * 4), static_cast<float>(0));
	right.setSize(sf::Vector2f(tileSize / 2 , windowHeight - (tileSize * 4)));
	right.setFillColor(sf::Color::Blue);

	bottom.setPosition(static_cast<float>((windowWidth - 160) - (tileSize * 16.55f)), static_cast<float>(windowHeight - (tileSize * 4)));
	bottom.setSize(sf::Vector2f(tileSize * 13.05f, tileSize / 2));
	bottom.setFillColor(sf::Color::Blue);
	
	//Setup UI 
	gui();

	//Create shapes and add them to the vector.
	Cube cube;
	Straight straight;
	ZShape zShape;
	LShape lShape;
	LShape2 lShape2;
	TShape TShape;
	SShape sShape;

	shapes.push_back(cube);
	shapes.push_back(straight);
	shapes.push_back(zShape);
	shapes.push_back(lShape);
	shapes.push_back(lShape2);
	shapes.push_back(sShape);
	shapes.push_back(TShape);

	//Set variables up to default values
	boardObj.create_board();
	currShape.setFalling(false);
}

void Game::run() 
{
	bool playing = true;
	//Seed 
	srand(static_cast<unsigned int>(time(nullptr)));
	std::cout << "Running!" << std::endl;

	randomPiece();

	//Add clause to catch if there's a shape above or in the top line.
	while(playing) {

		//Get start time.
		std::chrono::high_resolution_clock::time_point beginTime = std::chrono::high_resolution_clock::now();

		//If the current shape is empty, it means there's nothing active.
		if(!currShape.isFalling()) {
			//Get next random piece, assign it to the next piece and set it on the board.
			currShape = nextShape;
			currShape.setFalling(true);
			randomPiece();
			//Reset start time of new shape.
			startTime = high_resolution_clock::now();
		}
		
		if(!emptyTopRow()){
			//TODO - Improve this, especially when adding states.
			std::cout << "GAME OVER!" << std::endl;
			std::cout << "You scored " << score << " points, " <<
				lineCount << " lines and reached level " << level
				<< " Well done!! " << std::endl;

			exit(0);
		}
		
		input();
		update();
		draw();

		//Calculate fps, set title to show the most recent frame time / fps.
		std::chrono::high_resolution_clock::time_point endTime = std::chrono::high_resolution_clock::now();
		float result = std::chrono::duration_cast<std::chrono::duration<float>>(endTime - beginTime).count();

		duration<long long, std::milli> frames = duration_cast<milliseconds>(endTime - beginTime);
		auto fps(1000 / frames.count());

		window.setTitle("Tetris Clone, Version 1 - FPS: " + std::to_string(fps));
	}
}

/*
	Draws the following elements:

	Clears the board
	Board
	Falling shape
	Border
	Next shape
	UI elements
	
	Then displays the window
*/

void Game::draw() 
{
	window.clear(sf::Color::Black);
	drawBoard();
	drawShape();
	drawBorder();
	drawNextShape();
	gui();
	window.display();
}

/*
	Draws the board by iterating through the vector.
*/

void Game::drawBoard() 
{
	for(int i = 0; i < tileSize; i++) {
		for(int j = 0; j < tileSize; j++) {
			if(boardObj.board[i][j].isFilled()) {
				boardObj.board[i][j].piece.setPosition(static_cast<float>(j*tileSize), static_cast<float>(i*tileSize));
				window.draw(boardObj.board[i][j].piece);
			}
		}
	}
}

/*
	Drops pieces of alloted time has passed and checks for whole lines.
*/

void Game::update() 
{
	//If enough time has passed, drop blocks.
	if(dropTimer()){
		dropPieces(false);
	}

	isWholeLine();
}


void Game::input() 
{
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
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)){
			exit(1);
		}

		//Left key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			boardObj.moveLeft(currShape);
		}
		//Right key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			boardObj.moveRight(currShape);	
		}
		//Down key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			dropPieces(false);
		}
		//Up key
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			boardObj.rotatePiece(currShape);
		}
		
		if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			dropPieces(true);
		}
    }
}

/*
	Draws the current shape on the screen
*/
void Game::drawShape()
{
	float floatX, floatY;
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 4; j++){
			if(currShape.layout[i][j] > 0){

				//Create proper sizes for the drawing of the shapes.
				floatX = static_cast<float>(currShape.getX() * tileSize + (j * 32));
				floatY = static_cast<float>(currShape.getY() * tileSize + (i * 32));

				currShape.piece.setPosition(floatX, floatY);
				window.draw(currShape.piece);
			}
		}
	}
}

/*
	Draws the next shape on the screen
*/
void Game::drawNextShape()
{
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

/*
	Responsible for drawining the parts of the border
*/

void Game::drawBorder()
{
	//Bucket border
	window.draw(left);
	window.draw(right);
	window.draw(bottom);
}

/*
	Randomises a piece from the vector or tetris_shape objects
	It sets the piece in the middle of screen (currently at X 7)
*/

void Game::randomPiece()
{
	nextShape = shapes[rand() % shapes.size()];
	nextShape.setX(7);
	nextShape.setY(0);
}

/*
	Checks if the top row is empty, used to check for end-game conditions
*/

bool Game::emptyTopRow()
{
	for(int j = 0; j < tileSize / 2; j ++){
		if(boardObj.board[0][j].isFilled()){
			return false;
		}
	}
	return true;
}


/*
	Checks if the line is full, i.e. the sum of the whole line is 
	equal to a certain number. For now, that number is 12.
*/
void Game::isWholeLine()
{
	//Sum for calculating a whole line.
	int sum;

	for(int i = 0; i < tileSize; i++) {
		sum = 0;
		for(int j = 0; j < tileSize / 2; j++) {
			if(boardObj.board[i][j].isFilled()) {
				sum++;
			}
		}

		if(sum == 12) {
			std::cout << "Whole line!" << std::endl;
			boardObj.clearLine(i);
			score += 10;
			lineCount++;
			//If it's divisible by 3 again, another 3 lines have been reached so
			//The level goes up.
			if(lineCount % 3 == 0) {
				std::cout << "Level up!" << std::endl;
				level++;
			}
		}
	}
}

/*
	Drops all pieces in the board down one space.
*/

void Game::dropPieces(const bool &toBottom) 
{

	//Move down
	currShape.setY(currShape.getY()+1);

	//If bottom or there is a collison, stop, else continue
	if(currShape.getY() >= 26 || boardObj.isCollision(currShape)) {

		currShape.setY(currShape.getY()-1);
		currShape.setFalling(false);
		boardObj.setPiece(currShape);
	} 

	if(toBottom && !boardObj.isCollision(currShape)) {
		dropPieces(true);
	}
}

/*
	Timer to check if a piece needs to drop down a line or not
	Currently calculated as:

	1 second - level * 20

	Level 1 is .5 of a second
*/

bool Game::dropTimer()
{
	//Set current last time to now.
	lastTime = high_resolution_clock::now();

	duration<double> lifeTime = milliseconds(500 - ((level - 1) * 20));

	//Force the speed to remain positive if it's gone below 0.0
	if(lifeTime.count() <= 0.0) {

		lifeTime = milliseconds(100);
	}

	if(lastTime >= startTime + lifeTime){

		//Reset time to current time
		startTime = high_resolution_clock::now();
		return true;
	} 

	return false;
}

/*
	Responsible for drawing the basic ui elements.
*/

void Game::gui() 
{

	sf::Font font;
	if (!font.loadFromFile("fonts/kenpixel.ttf"))
	{
		std::cerr << " Error loading font!" << std::endl;
		exit(1);
	}

	sf::Text next;
	sf::Text lines_text;
	sf::Text level_text;

	//Add to vector of elements
	guiText.push_back(next);
	guiText.push_back(lines_text);
	guiText.push_back(level_text);

	std::string text = "";

	next.setFont(font);
	next.setPosition(windowWidth - (tileSize * 8), 80);

	next.setString("Next: ");
	next.setCharacterSize(24);
	next.setColor(sf::Color::White);
	next.setStyle(sf::Text::Bold | sf::Text::Underlined);

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
	window.draw(lines_text);

}
