#ifndef BALLS_H
#define BALLS_H
#include "raylib.h"

namespace Ignacio {
	const int ballMax = 20;

	struct Ball {
		Vector2 ballSpeed;
		Vector2 ballPosition;
		int radius;
		bool active;
	};

	extern Ball balls[ballMax];
	void setBallParameters();
	void initBallSpeed();
	void multiplyBall(int &counterBall);
}
#endif