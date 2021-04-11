#pragma once
#include "Actor.h"
class Charater :
	public Actor
{
public:
	Charater(float x, float y, float h, float w);
	void attack();
	void stopAttack();
	void jump();
	void land();
	void fall();
	bool collide();
	void reset();
	void setDead();
	bool getDead();
	void update();
	bool getAttacking();
	bool animation();
	void setYVel(float y);
	bool moving();
	
	~Charater();

private:
	bool attacking = false;
	bool reachedJumpHigh = false;
	float trueJumpHigh = 150;
	float jumpHeight = 0;
	bool landed = true;
	float animatingShift = 10000000;
	float hold = 0;
	bool dead = false;
};

