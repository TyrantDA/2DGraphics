#include "Enemy.h"
#include "Engine.h"


Enemy::Enemy(float x, float y, float h, float w, float distance)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	originX = x;
	originY = y;
	moveDistance = distance;
	speed = 500;
	textureFix();
}

bool Enemy::drop()
{
	if (ypos < 1000)
	{
		ypos = originY;
		xpos -= speed * detalTime;
		return true;
	}
	return false;
}

bool Enemy::collide()
{
	for (Actor* a : colList) {
		if (isCol(a))
		{
			return true;	
		}
	}
	return false;
}

void Enemy::update()
{
		xpos -= speed * detalTime;
		moveSoFar -= speed;
		
		if (abs(moveSoFar) > moveDistance)
			speed = -speed;

		if (grounded)
		{
			if (ypos != originY)
			{
				speed = -speed;
				ypos = ypos + 20;
				grounded = false;
			}
		}

		if (!collide())
		{
			ypos -= 100 * detalTime;
		}
		else if (collide())
		{
			originY = ypos;
			grounded = true;
		}

}

float Enemy::getSpeed() {
	return speed;
}


Enemy::~Enemy()
{
}
