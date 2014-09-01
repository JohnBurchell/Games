#include "tileMap.h"
#include "sprite.h"

using std::vector;

class Sprite;

TileMap::TileMap()
{

}

TileMap* TileMap::generateDebugMap(Graphics& graphics)
{
	TileMap* map = new TileMap();

	//Match the rows and cols to be correct multiples of the level size.
	const int num_rows = 40;
	const int num_cols = 50;

	map->mapTiles = vector < vector < Tile > >(num_rows, vector < Tile >(num_cols, Tile()));

	std::shared_ptr<Sprite> testSprite{ new Sprite(graphics, "resources/background/PrtCave.bmp", 32, 0, 32, 32) };

	Tile tile{ testSprite, TileType::WALL };

	for (int col = 0; col < num_cols; ++col) {
		map->mapTiles[15][col] = tile;
	}

	map->mapTiles[15][40] = Tile();

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
	map->mapTiles[13][7] = tile;
	map->mapTiles[12][6] = tile;

	map->mapTiles[14][9] = tile;
	map->mapTiles[13][9] = tile;

	map->mapTiles[13][10] = tile;
	map->mapTiles[15][10] = tile;

	map->mapTiles[12][15] = tile;
	map->mapTiles[14][14] = tile;
	map->mapTiles[13][15] = tile;
	map->mapTiles[12][14] = tile;
	map->mapTiles[12][13] = tile;


	return map;
}

std::vector<BoundingBox> TileMap::getCollisionTiles() const
{
	std::vector<BoundingBox> collisionTiles;

	//TODO - Optimise later - notably find the area around the "potentially" colliding box

	for (size_t i = 0; i < mapTiles.size(); ++i) {
		for (size_t j = 0; j < mapTiles[i].size(); ++j) {
			if (mapTiles[i][j].type_ == TileType::WALL) {
				collisionTiles.emplace_back(BoundingBox{ static_cast<float>(j * 32), static_cast<float>(i * 32) });
			}
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
				//mapTiles[row][col].sprite_->update(time_ms);
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