#pragma once
#include "raylib.h"
#include "gameManager.h"

const int barrierMax = 2;

struct Barrier {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	bool active;
};

extern Barrier barriers[barrierMax];
void setBarrierParameters();