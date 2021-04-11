#include "Charater.h"
#include "Engine.h"


Charater::Charater(float x, float y, float h, float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	textureFix();
}

void Charater::attack()
{
	attacking = true;
}

void Charater::stopAttack()
{
	attacking = false;
}

void Charater::jump()
{
	//jumpHeight = trueJumpHigh;
	if (landed) {
		ypos += 1;
		yVel = 3500;
		landed = false;
	}
		
	//std::cout << "Up: " << yVel << std::endl;
}

void Charater::land()
{
	landed = true;
}

void Charater::fall()
{
	landed = false;
}

bool Charater::collide()
{
	for (Actor* a : colList) {
		if (isCol(a))
		{
			return true;
			//xpos -= xVel;
		}
	}
	for (MovingPlatform* m : moveList)
	{
		if (isCol(m))
		{
			return true;
		}
	}
	return false;
}

void Charater::reset() {
	dead = true;
}

void Charater::setDead()
{
	dead = false;
}

bool Charater::getDead()
{
	return dead;
}

void Charater::update() {
	float offMap = 0;

	xpos += xVel * detalTime;
	if (collide())
	{
		xpos -= xVel * detalTime;
	}
	ypos += yVel * detalTime;
	if (collide())
	{
		ypos -= yVel * detalTime;
		if (yVel <= 0)
		{
			landed = true;
		}
	}
	
	if (!landed) {
		yVel -= 20000 * detalTime;
	}
	else {
		yVel = 0;
	}
	
	if (attacking)
	{
		spin += 1;
	}
	else {
		spin = 0;
	}

	if (ypos <= offMap)
	{
		reset();
	}
}

bool Charater::getAttacking()
{
	return attacking;
}

bool Charater::animation() {
	hold += detalTime;
	hold = hold * 1000;
	float compare = animatingShift/hold;
	if (animatingShift <= hold)
	{
		hold = 0;
		std::cout << "true" << std::endl;
		return true;
	}
	else
	{
		std::cout << "false" << std::endl;
		return false;
	}
}

void Charater::setYVel(float y)
{
	yVel = y;
	ypos += yVel * detalTime;
}

bool Charater::moving()
{
	if (xVel > 0 || xVel < 0)
	{
		return true;
	}
	else {
		return false;
	}
}


Charater::~Charater()
{
}
