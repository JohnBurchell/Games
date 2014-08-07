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

	player.reset(new Player(graphics, 6, 12));
	Camera camera(6 * 32, 12 * 32);

	//Map required to return a static map.
	map.reset(TileMap::generateDebugMap(graphics));

	for (;;) {

		auto frameStart = SDL_GetTicks();

		//TODO - Get the scrolling working first, it'll probably be the hardest part!
		//Add a camera that only focuses on the play and moves with them, get it working horizontally first
		//then add in vertical movement with jumps etc

		if (player->x_ * 32 < Constants::LEVEL_SIZE) {
			++player->x_;
		}

		if (player->x_ * 32 >= Constants::LEVEL_SIZE) {
			player->x_ = 0;
		}
		
		camera.update(player->x_, player->y_);

		std::cout << "Player x is at : " << player->x_ << std::endl;

		graphics.clear();
		map->draw(graphics);
		player->draw(graphics);
		graphics.flip();

		SDL_Delay(frameStart + 30.0f - SDL_GetTicks());;
	}
}

Game::~Game()
{
	SDL_Quit();
}
