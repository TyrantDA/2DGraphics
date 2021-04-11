#include "MovingPlatform.h"
#include "Engine.h"


MovingPlatform::MovingPlatform(float x, float y, float h, float w, float distance)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	moveDistance = distance;
	speed = 100;
	Actor::texture(2);
}

void MovingPlatform::update()
{

	ypos -= speed * detalTime;
	moveSoFar += speed;

	if (abs(moveSoFar) > moveDistance)
		speed = -speed;


}

float MovingPlatform::getSpeed()
{
	return speed;
}


MovingPlatform::~MovingPlatform()
{
}
