#include "gameManager.h"

void play() {
	InitWindow(screenWidth, screenHeight, "Pongacho");
	update();
	CloseWindow();
}

void setAllParameters() {
	//Players
	setPlayerParameters();

	//Barriers
	setBarrierParameters();

	//Balls
	setBallParameters();
}

void inputs() {
	if (IsKeyDown(KEY_W)) players[0].rec.y -= movementSpeed;
	if (IsKeyDown(KEY_S)) players[0].rec.y += movementSpeed;

	if (IsKeyDown(KEY_UP)) players[1].rec.y -= movementSpeed;
	if (IsKeyDown(KEY_DOWN)) players[1].rec.y += movementSpeed;
}

void update() {
	menu();
}

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

void getSizeUp(int whichPlayer) {
	players[whichPlayer].rec.height += 1.0f;
	barriers[whichPlayer].rec.height += 1.0f;
}

void changeColor(int &counterColor, Color &background) {
	if (counterColor % 2 == 0) {
		players[0].playerColor = BLACK;
		players[1].playerColor = BLACK;
		background = WHITE;
	}
	else {
		players[0].playerColor = WHITE;
		players[1].playerColor = WHITE;
		background = BLACK;
	}
	if (counterColor >= 1) {
		counterColor = 0 - 1;
	}
	counterColor++;
}