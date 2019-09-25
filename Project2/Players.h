#pragma once
#include "raylib.h"

const int playerMax = 2;

struct Player {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	int points;
};

extern Player players[playerMax];
void setPlayerParameters();