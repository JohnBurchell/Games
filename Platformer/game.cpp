#include "game.h"
#include "graphics.h"
#include "sprite.h"

#include <algorithm>
#include <memory>

//Forward declarations
class Graphics;
class Sprite;
class Player;
class Enemy;
class Projectile;
class TestEnemy;

namespace
{
	const int FPS = 60;
	const int MAX_FRAME_TIME = 5 * 1000 / 60;
}

Game::Game()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Error initialising SDL! " << SDL_GetError() << std::endl;
	}
	run();
}

void Game::updateCamera(Camera& camera)
{
	auto position = player->getPosition();
	camera.x = (position.x + Constants::TILE_WIDTH - Constants::SCREEN_WIDTH / 2);
	camera.y = (position.y + Constants::TILE_HEIGHT - Constants::SCREEN_HEIGHT / 2);

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

	player.reset(new Player(graphics, 4 * 32, 4 * 32));

	enemies.emplace_back(new Enemy(graphics, 8 * 32, 4 * 32));

	map.reset(map->generateDebugMap(graphics));

	Camera camera { Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };

	uint32_t previousFrameTime = SDL_GetTicks();

	static auto startTime = SDL_GetTicks();

	while(true) {

		uint32_t frameStart = SDL_GetTicks();

		SDL_Event e;

		//This is bad - Consider having something observe the player report on movements?
		auto pos = player->getPosition();

		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_KEYDOWN){
				switch (e.key.keysym.sym) {
				case SDLK_RIGHT:
					player->startMovingRight();
					break;
				case SDLK_LEFT:
					player->startMovingLeft();
					break;
				case SDLK_UP:
					player->startJump();
					break;
				case SDLK_BACKSPACE:
					enemies.emplace_back(new Enemy(graphics, 8 * 32, 4 * 32));
					break;
				case SDLK_RETURN:
					projectiles.emplace_back( 
						new Projectile(graphics, 
									   pos.x, 
									   pos.y,
									   player->getVelocity() >= 0 ? 0.6f : -0.6f));
					break;
				case SDLK_F12:
					player->enableDebug();
					break;
				case SDLK_q:
					enemies[0]->isInLineOfSight(player->getPosition(), enemies[0]->getPosition());
					break;
				case SDLK_ESCAPE:
					exit(0);
					break;
				}
			}

			else if (e.type == SDL_KEYUP){
				switch (e.key.keysym.sym) {
					case SDLK_RIGHT:
						player->stopMoving();
					case SDLK_LEFT:
						player->stopMoving();
				}
			}
		}

		uint32_t currentTime = SDL_GetTicks();
		const int timeSpentThisFrame = currentTime - previousFrameTime;

		update(std::min(timeSpentThisFrame, MAX_FRAME_TIME));
		updateCamera(camera);

		previousFrameTime = currentTime;
		draw(graphics, camera);

		uint32_t target_ms = 1000 / FPS;
		const int elapsedTime = SDL_GetTicks() - frameStart;
		const auto test = SDL_GetTicks() - startTime;

		if (elapsedTime < target_ms) {
			//Do nothing - Waste time to reach limit frame rate.
			SDL_Delay(target_ms - elapsedTime);
		}
	}
}

void Game::update(uint32_t time_ms)
{
	player->update(time_ms, *map);
	auto pos = player->getPosition();

	for(auto& x : enemies) {
		x->updatePlayerData(pos.x, pos.y);
		x->update(time_ms, *map);
	}

	for (auto& x : projectiles) {
		x->update(time_ms, *map);

		for(auto& y : enemies) {
			if(y->getDamageRectangle().boxCollision(x->getDamageRectangle(0))){
				y->takeDamage();
				x->collision();
			}
		}
	}

	for(auto& x : enemies)
	{
		if(player->getDamageRectangle().boxCollision(x->getDamageRectangle()))
		{
			player->takeDamage();
		}
	}

	auto predicate = [=](std::unique_ptr<Projectile>& a) { return a->hasCollided(); };
	auto predicateEnemy = [=](std::unique_ptr<Enemy>& a) { return !a->isAlive(); };

	if(projectiles.size() > 0 ){
		projectiles.erase(std::remove_if(std::begin(projectiles), std::end(projectiles), predicate), std::end(projectiles));
	}
	if(enemies.size() > 0 ){
		enemies.erase(std::remove_if(std::begin(enemies), std::end(enemies), predicateEnemy), std::end(enemies));
	}
}

void Game::draw(Graphics& graphics, Camera& camera)
{
	graphics.clear();
	map->draw(graphics, camera.x, camera.y);
	player->draw(graphics, camera.x, camera.y);

	for (auto& x : projectiles) {
		x->draw(graphics, camera.x, camera.y);
	}

	for(auto& x : enemies) {
		x->draw(camera.x, camera.y);
	}

	graphics.flip();
}

Game::~Game()
{
	SDL_Quit();
}

