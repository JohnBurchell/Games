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
		void draw(Graphics& graphics, float cameraX, float cameraY) const;
		void drawBackground(Graphics& graphics);

		//Possibly remove this later or keep just for testings?
		TileMap* generateDebugMap(Graphics& graphics);

		enum class TileType 
		{
			WALL,
			AIR
		};

		class CollisionTile
		{
			public:
				CollisionTile(int x, int y, TileType type) :
					x_(x),
					y_(y),
					type_(type)

				{};

				int x_, y_;
				TileType type_;
		};

		std::vector< BoundingBox > getCollisionTiles() const;
		std::vector< BoundingBox > getCollisionTilesTest(const BoundingBox& box) const;


	private:

		//TO-DO
		//Background Images - If doing Parallax then I'll need 3
		//Background Sprites
		//Foreground Sprites:
		//	Projectiles, other things?
		//Decide how to read a file containing map information, probably have this in a text / binary doc that I read whenever i'm loading a level.

		class Tile
		{
			public:
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