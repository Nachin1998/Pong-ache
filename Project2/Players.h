#pragma once
#include "raylib.h"
struct Player {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	int points;
};
const int playerMax = 2;
extern Vector2 size;
extern Player players[playerMax];