#ifndef ACTOR_H_
#define ACTOR_H_

#ifdef _WIN32
#pragma once
#endif

#include "graphics.h"
#include "tileMap.h"
#include "sprite.h"

class Actor
{
	public:
		virtual ~Actor() = 0;
		virtual void draw(Graphics& graphics, const float x, const float y) = 0;
		virtual void update(const uint32_t time, TileMap& map) = 0;
};

//MUST INLINE PURE VIRTUAL DESTRUCTOR
inline Actor::~Actor() {}

#endif //ACTOR_H_