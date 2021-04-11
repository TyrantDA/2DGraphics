#include "screen.h"



screen::screen(float x, float y, float h, float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	textureFix();
}

void screen::screenHeight(float h)
{
	ypos = h/2;
	height = h;
	textureFix();
}

void screen::screenWidth(float w)
{
	xpos = w / 2;
	width = w;
	textureFix();
}



screen::~screen()
{
	xpos = 0;
	ypos = 0;
	height = 0;
	width = 0;
}
