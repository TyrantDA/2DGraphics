#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <chrono>
#include "Actor.h"
#include "Charater.h"
#include "Goal.h"
#include "Enemy.h"
#include "MovingPlatform.h"
#include "EnemyIntercept.h"
#include "screen.h"
#include "Background.h"

extern float detalTime;
extern std::vector<Actor*> colList;
extern std::vector<MovingPlatform*> moveList;
extern std::vector<EnemyIntercept*> interceptList;