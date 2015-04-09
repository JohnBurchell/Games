#include "animated_sprite.h"

/*
	Creates an animated sprite
	Requires a reference to the graphics object
	Requires a filename of the sprite sheet associated with the animted sprite
	Float x and y for position
	Starts in an idle pose (i.e. position 0 in the sprite sheet)
	Starts facing left (i.e. position 0 in the y in the sprite sheet)
*/
Animated_Sprite::Animated_Sprite(Graphics& graphics, std::string fileName, const float x, const float y, sprite_pose starting_pose, sprite_facing starting_facing) :
Sprite(graphics, fileName, x, y, 32, 32),
m_current_frame{0},
m_current_sprite_pose{ starting_pose },
m_current_facing{ starting_facing }
{
	const int height = 32, width = 32;

	//Setup clipping rectangle boundaries
	for (int i = 0; i < 7; ++i)
	{
		m_sprite_clipping_rects[i] = SDL_Rect{ i * 32, 0, width, height };
	}
	//Set clipping rects for the next row (Right side)
	for (int i = 6; i < 12; ++i)
	{
		m_sprite_clipping_rects[i] = SDL_Rect{ (i-6) * 32, 32, width, height };
	}
}

void Animated_Sprite::update_sprite()
{
	//Consider using time to smooth the animations out, they're a little jerky right now.
	//i.e. 15ms per frame change?
	int facing_offset = (int)m_current_facing * 6;

	if (m_current_sprite_pose == sprite_poses::IDLE)
	{
		//Add idle animation to sheet
		m_current_frame = 0;
		m_source_rectangle = m_sprite_clipping_rects[m_current_frame + facing_offset];
	}
	else
	{
		++m_current_frame;
		m_current_frame = m_current_frame % 3;
		m_source_rectangle = m_sprite_clipping_rects[m_current_frame + facing_offset];
	}
}

void Animated_Sprite::set_pose(sprite_poses pose)
{
	m_current_sprite_pose = pose;
}

void Animated_Sprite::set_facing(sprite_facings facing)
{
	m_current_facing = facing;
}



