#include "Actor.h"
class Goal :
	public Actor
{
public:
	Goal(float x, float y, float h, float w);
	void reached();
	bool getReach();
	void update();
	~Goal();

private:
	bool reach;
};