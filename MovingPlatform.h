#pragma once
#include "Actor.h"
class MovingPlatform :
	public Actor
{
public:
	MovingPlatform(float x,float y, float h, float w, float distance);
	void update();
	float getSpeed();
	~MovingPlatform();

private:
	float moveDistance;
	float speed;
	float startingPlace;
	float moveSoFar = 0;
};

