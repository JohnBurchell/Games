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

	player.reset(new Player(graphics, 0, 0));
	//Map required to return a static map, due to missing rvalue probably?
	map.reset(TileMap::generateDebugMap(graphics));

	Camera camera { Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };

	SDL_Event event;

	for (;;) {

		auto frameStart = SDL_GetTicks();

		//TODO - Get the scrolling working first, it'll probably be the hardest part!
		//Add a camera that only focuses on the play and moves with them, get it working horizontally first
		//then add in vertical movement with jumps etc

		while (SDL_PollEvent(&event) != 0) {
			player->handleEvent(event);
		}

		camera.x = (player->getXpos() - Constants::SCREEN_WIDTH  / 2);
		camera.y = (player->getYpos() - Constants::SCREEN_HEIGHT / 2);

		if (camera.x < 0)
		{
			camera.x = 0;
		}
		if (camera.y < 0)
		{
			camera.y = 0;
		}
		if (camera.x > Constants::LEVEL_WIDTH - camera.w)
		{
			camera.x = Constants::LEVEL_WIDTH - camera.w;
		}
		if (camera.y > Constants::LEVEL_HEIGHT - camera.h)
		{
			camera.y = Constants::LEVEL_HEIGHT - camera.h;
		}

		update(0);
		draw(graphics, camera);

		std::cout << player->getYpos() << std::endl;
	}
}

void Game::update(int delta)
{
	player->update(delta);
}

void Game::draw(Graphics& graphics, Camera& camera)
{
	graphics.clear();
	map->draw(graphics, camera.x, camera.y);
	player->draw(graphics, camera.x, camera.y);
	graphics.flip();
}

Game::~Game()
{
	SDL_Quit();
}
