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

	player.reset(new Player(graphics, 4 * 32, 4 * 32));

	enemies.emplace_back(new Enemy(graphics, 8 * 32, 4 * 32));

	map.reset(map->generateDebugMap(graphics));

	Camera camera { Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT };

	uint32_t previousFrameTime = SDL_GetTicks();

	for (;;) {

		uint32_t frameStart = SDL_GetTicks();

		SDL_Event e;

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
									   player->getXpos(), 
									   player->getYpos(),
									   //Dirty - But it'll do for now
									   player->getVelocity() >= 0 ? 0.5f : -0.5f));
					break;
				case SDLK_F12:
					player->enableDebug();
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
	player->update(time_ms, *map);

	auto playerX = player->getXpos();
	auto playerY = player->getYpos();

	for(auto& x : enemies) {
		x->updatePlayerData(playerX, playerY);
		x->update(time_ms, *map);
	}

	for (auto& x : projectiles) {
		x->update(time_ms, *map);

		for(auto& y : enemies) {
			if(y->getDamageRectangle().boxCollision(x->getDamageRectangle())){
				y->takeDamage();
				x->collision();
			}

			if (player->getDamageRectangle().boxCollision(y->getDamageRectangle())) {
				//This check might not be needed, not sure if enemies are going to shoot at all.
				player->takeDamage();
			}
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
		x->draw(graphics, camera.x, camera.y);
	}

	graphics.flip();
}

Game::~Game()
{
	SDL_Quit();
}

