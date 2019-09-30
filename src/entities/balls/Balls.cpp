#include "Balls.h"

#include "game_manager/variables.h"

namespace IgnacioFernandezLemos {
	Ball balls[ballMax];


	void setBallParameters() {
		for (int i = 0; i < ballMax; i++)
		{
			balls[i].ballPosition = ballPositionInit;
			balls[i].ballSpeed.x = 290.0f * GetFrameTime();
			balls[i].ballSpeed.y = 290.0f * GetFrameTime();
			balls[i].radius = 5;
			balls[i].active = false;
		}
		balls[0].active = true;
	}

	void initBallSpeed() {
		for (int i = 0; i < ballMax; i++)
		{
			if (balls[i].active == true) {
				balls[i].ballPosition.x += balls[i].ballSpeed.x;
				balls[i].ballPosition.y += balls[i].ballSpeed.y;
			}
		}
	}

	void multiplyBall(int &counterBall) {
		counterBall++;

		if (counterBall <= ballMax) {
			balls[counterBall].active = true;
		}

		for (int i = counterBall; i < ballMax; i++)
		{
			if (balls[i].active == true) {
				balls[i].ballPosition = balls[0].ballPosition;
				if (i % 2 == 0)
					balls[i].ballSpeed.x *= -1.1f;
				else
					balls[i].ballSpeed.y *= -1.1f;

			}
		}
	}
}