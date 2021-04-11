#pragma once
#include <iostream>
#include <windows.h>		// Header file for Windows
#include <gl\gl.h>			// Header file for the OpenGL32 Library
#include <gl\glu.h>			// Header file for the GLu32 Library


class Actor
{
public:
	Actor();
	Actor(float x, float y,float h, float w);
	void display();
	void texture(int a);
	void textureFix();
	void colour(float r, float g, float b);
	~Actor();
	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();
	void stop();
	bool isCol(Actor* a);
	float getXpos();
	float getYpos();
	float getMinX();
	float getMaxX();
	float getMinY();
	float getMaxY();
	float getXVel();
	virtual void update();

protected:
	float xpos;
	float ypos;
	float height;
	float width;
	float xVel;
	float yVel;
	float speed = 0;
	float spin = 0;
	float array[8] = { 512,512,147,236,689,1000};
	float x = 0;
	float y = 0;
};

