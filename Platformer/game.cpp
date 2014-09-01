#include "game.h"
#include "graphics.h"
#include "sprite.h"
#include "input.h"

//Forward declarations
class Graphics;
class Sprite;
class InputHandler;
class Player;
class Enemy;

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initialising SDL! " << SDL_GetError() << std::endl;
	}
	run();
}

void Game::updateCamera(Camera& camera)
{
	camera.x = (player->getXpos() + Constants::TILE_WIDTH - Constants::SCREEN_WIDTH / 2);
	camera.y = (player->getYpos() + Constants::TILE_HEIGHT - Constants::SCREEN_HEIGHT / 2);

	if (camera.x < 0) {
		camera.x = 0;
	}
	if (camera.y < 0) {
		camera.y = 0;
	}
	if (camera.x > Constants::LEVEL_WIDTH - camera.w) {
		camera.x = Constants::LEVEL_WIDTH - camera.w;
	}
	if (camera.y > Constants::LEVEL_HEIGHT - camera.h) {
		camera.y = Constants::LEVEL_HEIGHT - camera.h;
	}
}

void Game::run()
{
	Graphics graphics;
	InputHandler inputHandler;

	player.reset(new Player(graphics, 6 * 32, 6 * 32));
	enemy.reset(new Enemy(graphics, 8 * 32, 8 * 32));

	map.reset(map->generateDebugMap(graphics));

	Camera camera { Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };

	
	uint32_t previousFrameTime = SDL_GetTicks();

	for (;;) {

		uint32_t frameStart = SDL_GetTicks();

		//TODO - Finish the input handler, get basic input working first, it'll be ugly but working!
		//inputHandler.handleInput();

		SDL_Event event;

		while (SDL_PollEvent(&event) != 0) {
			player->handleEvent(event);
		}

		uint32_t currentTime = SDL_GetTicks();
		uint32_t timeSpentThisFrame = currentTime - previousFrameTime;

		update(timeSpentThisFrame);
		updateCamera(camera);
		draw(graphics, camera);
		
		previousFrameTime = SDL_GetTicks();

		uint32_t target_ms = 1000 / 60;

		while (timeSpentThisFrame < target_ms) {
			//Do nothing - Waste time to reach limit frame rate.
			timeSpentThisFrame = SDL_GetTicks() - frameStart;
		}
	}
}

void Game::update(uint32_t time_ms)
{
	enemy->update(time_ms, *map);
	player->update(time_ms, *map);
}

void Game::draw(Graphics& graphics, Camera& camera)
{
	graphics.clear();
	map->draw(graphics, camera.x, camera.y);

	enemy->updatePlayerData(player->getXpos(), player->getYpos());
	enemy->draw(graphics, camera.x, camera.y);

	player->draw(graphics, camera.x, camera.y);
	graphics.flip();
}

Game::~Game()
{
	SDL_Quit();
}

