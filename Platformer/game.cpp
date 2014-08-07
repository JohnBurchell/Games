#include "game.h"
#include "graphics.h"
#include "sprite.h"

//Forward declarations
class Graphics;
class Sprite;

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initialising SDL! " << SDL_GetError() << std::endl;
	}
	run();
}

void Game::run()
{
	Graphics graphics;
	Sprite sprite(graphics, "resources/sprites/MyChar.bmp", 0, 0, 32, 32);

	//Map required to return a static map.
	map.reset(TileMap::generateDebugMap(graphics));

	int test =  Constants::SCREEN_HEIGHT / 2;
	int test2 = Constants::SCREEN_WIDTH / 2;

	for (;;) {

		//TODO - Get the scrolling working first, it'll probably be the hardest part!
		//Add a camera that only focuses on the play and moves with them, get it working horizontally first
		//then add in vertical movement with jumps etc
		graphics.clear();
		map->draw(graphics);
		sprite.draw(graphics, test, test2);
		graphics.flip();
	}
}

Game::~Game()
{
	SDL_Quit();
}
