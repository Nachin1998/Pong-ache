#ifndef VARIABLES_H
#define VARIABLES_H
#include "raylib.h"

namespace IgnacioFernandezLemos {
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int powerUpMax = 20;
	const int movementSpeed = 300;
	const int win = 100;
	const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
	const Vector2 size = { 18.0f, 120.0f };

	extern Color background;
	extern int counterColor;
	extern int counterTiempo;
	extern int counterBall;
}
#endif
