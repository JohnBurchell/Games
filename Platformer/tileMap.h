#ifndef TILEMAP_H_
#define TILEMAP_H_
#pragma once

#include <vector>

#include "common.h"
#include "sprite.h"

class Sprite;

class TileMap
{
	public:
		TileMap();
		~TileMap();

		void update(int delta);
		void draw(Graphics& graphics) const;
		void drawBackground(Graphics& graphics);

		//Possibly remove this later or keep just for testings?
		static TileMap* generateDebugMap(Graphics& graphics);

	private:

		//TO-DO
		//Background Images - If doing Parallax then I'll need 3
		//Background Sprites
		//Foreground Sprites
		//Types of tiles - Air, Ground, Water?
		//Decide how to read a file containing map information, probably have this in a text / binary doc that I read whenever i'm loading a level.
		//I need to figure out how to do the scrolling too, it might be tricky!

		struct Tile 
		{
			Tile(std::shared_ptr<Sprite> sprite = std::shared_ptr<Sprite>()) :

				sprite_(sprite)

			{};

			void draw(Graphics& graphics);
			std::shared_ptr<Sprite> sprite_;
		};

		//Container for the tiles.
		std::vector < std::vector< Tile > > mapTiles;
};


#endif //TILEMAP_H_