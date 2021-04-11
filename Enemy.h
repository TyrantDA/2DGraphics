#pragma once
#include "Actor.h"
class Enemy :
	public Actor
{
public:
	Enemy(float x, float y, float h, float w, float distance);
	bool drop();
	bool collide();
	void update();
	float getSpeed();
	~Enemy();

private:
	float moveDistance;
	float speed;
	float originX;
	float originY;
	bool grounded =false;
	float moveSoFar = 0;
};

