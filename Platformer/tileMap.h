#ifndef TILEMAP_H_
#define TILEMAP_H_
#pragma once

#include <vector>

#include "common.h"
#include "sprite.h"
#include "boundingBox.h"

class Sprite;
class BoundingBox;

class TileMap
{
	public:
		TileMap();
		~TileMap();

		void update(int delta);
		void draw(Graphics& graphics, int cameraX, int cameraY) const;
		void drawBackground(Graphics& graphics);

		//Possibly remove this later or keep just for testings?
		static TileMap* generateDebugMap(Graphics& graphics);

		enum class TileType 
		{
			WALL,
			AIR,
			WATER
		};

		struct CollisionTile
		{
			CollisionTile(int x, int y, TileType type) :
				x_(x),
				y_(y),
				type_(type)

			{};

			void draw(Graphics& graphics, int cameraX, int cameraY) const { graphics.render_rectanlge(x_ * 32 - cameraX, y_ * 32 - cameraY, 5); };
			int x_, y_;
			TileType type_;
		};

		std::vector< CollisionTile > getCollisionTiles(BoundingBox& collider) const;

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
			Tile(std::shared_ptr<Sprite> sprite = std::shared_ptr<Sprite>(), TileType type = TileType::AIR) :

				sprite_(sprite),
				type_(type)
			{};

			void draw(Graphics& graphics);
			std::shared_ptr<Sprite> sprite_;
			TileType type_;
		};

		//Container for the tiles.
		std::vector < std::vector< Tile > > mapTiles;
};


#endif //TILEMAP_H_