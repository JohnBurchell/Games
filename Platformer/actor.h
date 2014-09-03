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
		virtual ~Actor() = 0;
		virtual void draw(Graphics& graphics, float x, float y) = 0;
		virtual void update(const uint32_t time, TileMap& map) = 0;

	private:
		float x_, y_;

		std::shared_ptr<Sprite> sprite_;
};

inline Actor::~Actor()
{
	//Implementation for derriving classes.
}

#endif //ACTOR_H_