#include "Goal.h"

Goal::Goal(float x, float y, float h, float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	reach = false;
	textureFix();
}

void Goal::reached()
{
	reach = true;
}

bool Goal::getReach()
{
	return reach;
}

void Goal::update()
{
}

Goal::~Goal()
{
}
