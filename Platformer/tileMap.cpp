#include "tileMap.h"
#include "sprite.h"

using std::vector;

class Sprite;

TileMap::TileMap()
{

}

TileMap* TileMap::generateDebugMap(Graphics& graphics)
{
	//TODO - Fill and create the test map.
	TileMap* map = new TileMap();

	//Match the rows and cols to be correct multiples of the screen size.
	const int num_rows = 40;
	const int num_cols = 50;

	map->mapTiles = vector < vector < Tile > >(num_rows, vector < Tile >(num_cols, Tile()));

	std::shared_ptr<Sprite> testSprite{ new Sprite(graphics, "resources/background/PrtCave.bmp", 32, 0, 32, 32) };

	Tile tile{ testSprite, TileType::WALL };

	for (int col = 0; col < num_cols; ++col) {
		map->mapTiles[15][col] = tile;
	}

	for (int col = 0; col < num_cols; ++col) {
		map->mapTiles[0][col] = tile;
	}

	for (int col = 0; col < num_cols; ++col) {
		map->mapTiles[39][col] = tile;
	}

	for (int row = 0; row < num_rows; ++row) {
		map->mapTiles[row][0] = tile;
	}

	for (int row = 0; row < num_rows; ++row) {
		map->mapTiles[row][49] = tile;
	}

	map->mapTiles[14][7] = tile;

	return map;
}

std::vector<TileMap::CollisionTile> TileMap::getCollisionTiles(BoundingBox& collider) const
{
	const int firstRow = collider.top() / 32;
	const int lastRow = collider.bottom() / 32;
	const int firstCol = collider.left() / 32;
	const int lastCol = collider.right() / 32;

	//std::cout << "----" << std::endl;
	//std::cout << firstRow << std::endl;
	//std::cout << lastRow << std::endl;
	//std::cout << firstCol << std::endl;
	//std::cout << lastCol << std::endl;
	//std::cout << "----" << std::endl;

	std::vector<TileMap::CollisionTile> collisionTiles;

	for (int row = firstRow; row <= lastRow; ++row){
		for (int col = firstCol; col <= lastCol; ++col) {
			collisionTiles.push_back(CollisionTile{ row, col, mapTiles[row][col].type_ });
		}
	}

	return collisionTiles;
}

void TileMap::update(int time_ms)
{
	//Cols measured in X, Rows in Y
	for (size_t row = 0; row < mapTiles.size(); ++row) {
		for (size_t col = 0; col < mapTiles[row].size(); ++col) {
			if (mapTiles[row][col].sprite_) {
				//TODO
			}
		}
	}
}

void TileMap::draw(Graphics& graphics, int cameraX, int cameraY) const
{
	//Cols measured in X, Rows in Y
	for (size_t row = 0; row < mapTiles.size(); ++row) {
		for (size_t col = 0; col < mapTiles[row].size(); ++col) {
			if (mapTiles[row][col].sprite_) {
				mapTiles[row][col].sprite_->draw(graphics, col * 32 - cameraX, row * 32 - cameraY);
			}
		}
	}

}

TileMap::~TileMap()
{

}