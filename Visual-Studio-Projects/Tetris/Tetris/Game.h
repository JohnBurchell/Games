#ifndef Game_H
#define Game_H

#include <SFML/Graphics.hpp>

#include <vector>
#include <chrono>

#include "Board.h"
#include "TetrisShape.h"
#include "TetrisShapes.h"

class Game {

public:

	Game();
	virtual ~Game();

	void run();

private:

	//Variables.
	sf::RenderWindow window;
	
	std::chrono::high_resolution_clock::time_point startTime;
	std::chrono::high_resolution_clock::time_point lastTime;

	std::vector<TetrisShape> shapes;
	std::vector<sf::Text> guiText;
	//Parts of the border
	sf::RectangleShape left;
	sf::RectangleShape bottom;
	sf::RectangleShape right;
	//Next piece container
	sf::RectangleShape box_left;
	sf::RectangleShape box_bottom;
	sf::RectangleShape box_right;
	sf::RectangleShape box_top;

	//Board
	Board boardObj;

	int score, level, timer, lineCount;	

	//Current falling shape.
	TetrisShape currShape, nextShape;

	//Memeber Methods.
	void update();
	void draw();
	void drawBoard();
	void drawShape();
	void drawNextShape();
	void drawBorder();
	void dropPieces(const bool &toBottom);
	void printBoard();
	void randomPiece();
	void setup();
	void input();

	void gui();

	//Check if a line needs to be removed or not.
	void isWholeLine();
	bool emptyTopRow();
	bool dropTimer();

};

#endif