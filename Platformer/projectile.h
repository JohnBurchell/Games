#ifndef PROJECTILE_H_
#define PROJECTILE_H_

#include "common.h"
#include "graphics.h"
#include "sprite.h"
#include "boundingBox.h"

class Graphics;
class Sprite;

class Projectile
{

	public:
		Projectile(Graphics& graphics, float x, float y);
		~Projectile();

		void draw(Graphics& graphics, float cameraX, float cameraY);
		void update(float delta);
	
		BoundingBox getDamageRectangle();

	private:
		float x_, y_;
		std::unique_ptr<Sprite> sprite_;
};

#endif //PROJECTILE_H_