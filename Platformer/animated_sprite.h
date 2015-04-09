#ifndef ANIMATED_SPRITE_H_
#define ANIMATED_SPRITE_H_

#include "sprite.h"
#include <string>

class Animated_Sprite : public Sprite
{

public:

	enum class sprite_poses
	{
		IDLE,
		MOVING_RIGHT,
		MOVING_LEFT,
		FALLING,
		JUMPING
	};

	enum class sprite_facings
	{
		FACING_LEFT,
		FACING_RIGHT,
		FACING_UP
	};

	using sprite_facing = Animated_Sprite::sprite_facings;
	using sprite_pose = Animated_Sprite::sprite_poses;

	explicit Animated_Sprite(Graphics& graphics, std::string filename, const float x, const float y, 
		sprite_pose starting_sprite = Animated_Sprite::sprite_poses::IDLE,
		sprite_facing starting_facing = Animated_Sprite::sprite_facings::FACING_LEFT);

	void update_sprite();
	void set_facing(sprite_facings facing);
	void set_pose(sprite_poses pose);
	inline sprite_facings get_facing() { return m_current_facing; };
	inline sprite_poses get_pose () { return m_current_sprite_pose; };

private:
	sprite_poses m_current_sprite_pose;
	sprite_facings m_current_facing;
	//Do I really need to pre-compute them? Does it save enough time to warrant the extra memory?
	SDL_Rect m_sprite_clipping_rects[12];
	int m_current_frame;
};

#endif //ANIMATED_SPRITE
