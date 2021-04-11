#include "Background.h"



Background::Background(float x, float y, float h, float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	texture(4);
}

void Background::backgroundTexture(int a)
{
		y = 1;
		x = x = width / array[a + 1];
}

void Background::move(float x)
{
	xpos = x;
}


Background::~Background()
{
}
