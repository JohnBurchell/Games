#ifndef ACTOR_H_
#define ACTOR_H_

#ifdef _WIN32
#pragma once
#endif

#include "graphics.h"
#include "tileMap.h"
#include "sprite.h"

class Graphics;
class TileMap;
class Sprite;

class Actor
{
	public:
		virtual ~Actor() = 0 { std::cout << "Base" << std::endl; };
		virtual void draw(Graphics& graphics, int x, int y) = 0;
		virtual void update(const uint32_t time, TileMap& map) = 0;

	private:
		float x_, y_;

		std::shared_ptr<Sprite> sprite_;
};

#endif //ACTOR_H_