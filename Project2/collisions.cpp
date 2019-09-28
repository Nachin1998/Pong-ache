#include "collisions.h"

#include "gameManager.h"

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
				if (i % 2 == 0)
					balls[i].ballPosition.x *= 1.5f;
				else
					balls[i].ballPosition.y *= 1.5f;
				balls[i].ballPosition = ballPositionInit;
				changeColor(counterColor, background);
			}

			//Detects the colision with the left scoring wall
			if (balls[i].ballPosition.x <= 0) {
				players[1].points++;
				getSizeUp(0);
				if (i % 2 == 0)
					balls[i].ballPosition.x *= 1.5f;
				else
					balls[i].ballPosition.y *= 1.5f;

				balls[i].ballPosition = ballPositionInit;
				changeColor(counterColor, background);
			}
		}
	}
}