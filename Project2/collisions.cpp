#include "collisions.h"

#include "Players.h"
#include "Balls.h"
#include "Barriers.h"

#include "variables.h"
#include "getSizeUp.h"

#include "changeColor.h"

#include <cstdlib>
#include <ctime>

namespace Ignacio {
	
	void collisions(int &counterBall, int &counterColor, Color &background) {

		for (int i = 0; i < ballMax; i++)
		{
			//Detects the colision with players and changes the color
			if (CheckCollisionCircleRec(balls[i].ballPosition, balls[i].radius, players[0].rec) ||
				CheckCollisionCircleRec(balls[i].ballPosition, balls[i].radius, players[1].rec)) {

				balls[i].ballSpeed.x *= -1.0f;
				if (balls[i].ballSpeed.x < 0) {
					balls[i].ballPosition.x -= 15;
					changeColor(counterColor, background);
				}
				else {
					balls[i].ballPosition.x += 15;
					changeColor(counterColor, background);
				}
			}

			//Detects the colision with shot barriers and changes the color
			if (CheckCollisionCircleRec(balls[i].ballPosition, balls[i].radius, barriers[0].rec) ||
				CheckCollisionCircleRec(balls[i].ballPosition, balls[i].radius, barriers[1].rec)) {
				balls[i].ballSpeed.x *= -1.0f;
				multiplyBall(counterBall);
				if (balls[i].ballSpeed.x < 0) {
					balls[i].ballPosition.x -= 15.0f;
					changeColor(counterColor, background);
				}
				else {
					balls[i].ballPosition.x += 15;
					changeColor(counterColor, background);
				}
			}

			//Detects the colision with walls and changes the color
			if ((balls[i].ballPosition.y >= (screenHeight - balls[i].radius)) || (balls[i].ballPosition.y <= balls[i].radius)) {
				balls[i].ballSpeed.y *= -1.0f;
				changeColor(counterColor, background);
			}

			//Detects the colision with the right scoring wall
			if (balls[i].ballPosition.x >= GetScreenWidth()) {
				players[0].points++;
				getSizeUp(1);

				balls[i].ballPosition.x = ballPositionInit.x +(rand() % 50);
				balls[i].ballPosition.y = ballPositionInit.y +(rand() % 50);
				changeColor(counterColor, background);
			}

			//Detects the colision with the left scoring wall
			if (balls[i].ballPosition.x <= 0) {
				players[1].points++;
				getSizeUp(0);

				balls[i].ballPosition.x = ballPositionInit.x +(rand() % 50);
				balls[i].ballPosition.y = ballPositionInit.y +(rand() % 50);
				changeColor(counterColor, background);
			}
		}
	}
}