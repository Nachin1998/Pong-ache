#pragma once
#include "raylib.h"

const int ballMax = 15;

struct Ball {
	Vector2 ballSpeed;
	Vector2 ballPosition;
	int radius;
	bool active;
};

extern Ball balls[ballMax];
void setBallParameters();