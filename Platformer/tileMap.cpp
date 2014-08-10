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

	Tile tile{testSprite};
	
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

	return map;
}

void TileMap::draw(Graphics& graphics, int cameraX, int cameraY) const
{
	for (size_t row = 0; row < mapTiles.size(); ++row){
		for (size_t col = 0; col < mapTiles[row].size(); ++col){
			if (mapTiles[row][col].sprite_) {
				mapTiles[row][col].sprite_->draw(graphics, col * 32 - cameraX, row * 32 - cameraY);
			}
		}
	}
}

TileMap::~TileMap()
{

}