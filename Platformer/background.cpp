#include "background.h"
#include "sprite.h"

class Sprite;

Background::Background(Graphics& graphics)
{
	texture = graphics.loadImage("resources/background/bkBlue.bmp", false);
}

Background::~Background()
{

}