#include "EnemyIntercept.h"
#include "Engine.h"

EnemyIntercept::EnemyIntercept(float x, float y, float h, float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	distance = y + 100;
	speed = 0;
	origin = y;
	textureFix();
}

void EnemyIntercept::collide()
{
	speed = 1000;
	col = true;
}

void EnemyIntercept::returnDown()
{
	speed = -1000;
}

void EnemyIntercept::update()
{ 
	if (col == true)
	{
		if (distance > ypos)
		{
			ypos += speed * detalTime;
		}
	}
	if (ypos <= origin)
	{
		col = false;
	}
}

bool EnemyIntercept::isColIntercept(Actor* a)
{
	return (this->getMinX() + 100) < a->getMaxX() && (this->getMaxX() + 100) > a->getMinX() && this->getMinY() < a->getMaxY() && (this->getMaxY() + 400) > a->getMinY();
}

EnemyIntercept::~EnemyIntercept()
{
}
