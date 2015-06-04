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

namespace Constants 
{
	using Tile = const int;
	Tile tile_size = 32;
	Tile left_indent = tile_size * 5;
	Tile next_shape_indent = tile_size * 16;

	const float fps = 60.0f;
	const float max_time = 5.0f * 1000 / fps;

	const int board_cols = 10, board_rows = 16;
	const int screen_height = (board_rows + 5) * tile_size;
	const int screen_width = (board_cols + 10)* tile_size;


} //constants

namespace Colours
{
	enum class Colour 
	{
		NONE,
		RED,
		GREEN,
		BLUE,
		TEAL,
		ORANGE,
		YELLOW,
		PURPLE,
		TRANS
	};
}


#endif //COMMON_H_