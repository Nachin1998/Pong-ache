#include "Balls.h"
#include "gameManager.h"
Ball balls[ballMax];

void setBallParameters() {
	for (int i = 0; i < ballMax; i++)
	{
		balls[i].ballPosition = ballPositionInit;
		balls[i].ballSpeed.x = 5.0f;
		balls[i].ballSpeed.y = 5.0f;
		balls[i].radius = 5;
		balls[i].active = false;
	}
	balls[0].active = true;
}