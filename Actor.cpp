#include "Actor.h"
#include "Engine.h"

Actor::Actor()
{
	xpos = 0;
	ypos = 0;
	height = 0;
	width = 0;
	xVel = 0;
	yVel = 0;
}

Actor::Actor(float x,float y,float h,float w)
{
	xpos = x;
	ypos = y;
	height = h;
	width = w;
	texture(0);
}

void Actor::display()
{
	//glPointSize(10.0f);
	//glBegin(GL_POINTS);
	//glVertex2i(mouse_x, mouse_y);
	//glEnd();

	glPushMatrix();
	glTranslatef(xpos, ypos, 0);
	glRotatef(spin,0,0,1);
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0f, y);			glVertex2f(-width/2, height/2);
	glTexCoord2f(0.0f, 0.0f);		glVertex2f(-width/2, -height/2);
	glTexCoord2f(x, 0.0f);			glVertex2f(width/2, -height/2);
	glTexCoord2f(x, y);				glVertex2f(width/2, height/2);
	glEnd();
	glPopMatrix();
}

void Actor::texture(int a)
{
	y = height / array[a];
	std::cout << y << std::endl;
	x = width / array[a+1];
	std::cout << x << std::endl;
}

void Actor::textureFix()
{
	y = 1;
	x = 1;
}

void Actor::colour(float r, float g, float b)
{
	glColor3f(r, g, b);
}


Actor::~Actor()
{
}

void Actor::moveLeft()
{
	xVel = -1000;
	//std::cout << "Left: " << xpos << std::endl;
}

void Actor::moveRight()
{
	//acc += 0.001f;
	xVel = 1000;
	//std::cout << "Right: " << xpos << std::endl;
}

void Actor::moveUp()
{
	//acc -= 0.001f;
	yVel = 1000;
	//std::cout << "Up: " << speed << std::endl;
}

void Actor::moveDown()
{
	//acc -= 0.001f;
	yVel = -1000;
	//std::cout << "Down: " << speed << std::endl;
}

void Actor::stop()
{
	xVel = 0;
}

bool Actor::isCol(Actor* a)
{
	return this->getMinX() < a->getMaxX() && this->getMaxX() > a->getMinX() && this->getMinY() < a->getMaxY() && this->getMaxY() > a->getMinY();
}

float Actor::getXpos()
{
	return xpos;
}

float Actor::getYpos()
{
	return ypos;
}

float Actor::getMinX()
{
	return (-(width/2) + xpos);
}

float Actor::getMaxX()
{
	return ((width/2) + xpos);
}

float Actor::getMinY()
{
	return (-(height/2) + ypos);
}

float Actor::getMaxY()
{
	return ((height/2) + ypos);
}

float Actor::getXVel()
{
	return xVel;
}

void Actor::update()
{
	xpos += xVel * detalTime;
	ypos += yVel * detalTime;
}




