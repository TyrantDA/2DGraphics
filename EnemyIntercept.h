#pragma once
#include "Enemy.h"
class EnemyIntercept :
	public Actor
{
public:
	EnemyIntercept(float x, float y, float h, float w);
	void collide();
	void returnDown();
	void update();
	bool isColIntercept(Actor* a);
	~EnemyIntercept();

private:
	float distance;
	bool col = false;
	float origin;
};

