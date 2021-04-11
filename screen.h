#pragma once
#include "Actor.h"
class screen :
	public Actor
{
public:
	screen(float x, float y, float h, float w);
	void screenHeight(float h);
	void screenWidth(float w);
	~screen();
};

