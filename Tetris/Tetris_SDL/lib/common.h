#ifndef COMMON_H_
#define COMMON_H_
#pragma once

#include <iostream>
#include <vector>
#include <chrono>
#include <utility>
#include <cerrno>
#include <memory>
#include <string>
#include <cassert>

namespace Constants {

	using Tile = const int;
	Tile TILE_SIZE = 32;
	Tile LEFT_INDENT = TILE_SIZE * 5;
	Tile NEXT_SHAPE_INDENT = TILE_SIZE * 16;

	const float FPS = 60.0f;
	const float MAX_TIME = 5.0f * 1000 / FPS;

	const int BOARD_COLS = 10, BOARD_ROWS = 16;
	const int SCREEN_HEIGHT = (BOARD_ROWS + 5)* TILE_SIZE, SCREEN_WIDTH = (BOARD_COLS + 10)* TILE_SIZE;


} //constants


#endif //COMMON_H_