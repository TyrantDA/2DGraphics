#pragma once
#include "Actor.h"
class Background :
	public Actor
{
public:
	Background(float x, float y, float h, float w);
	void backgroundTexture(int a);
	void move(float x);
	~Background();
};

