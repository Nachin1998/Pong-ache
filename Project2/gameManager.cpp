#include "gameManager.h"
#include "Audio.h"

Vector2 size = { 18.0f, 120.0f };

void game() {

	PlayMusicStream(gameMusic);

	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counterBall = 0;

	//Players
	setPlayerParameters();

	//Barriers
	setBarrierParameters();

	//Balls
	setBallParameters();

	//SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(gameMusic);

		ClearBackground(background);

		if (IsKeyDown(KEY_W)) players[0].rec.y -= movementSpeed;
		if (IsKeyDown(KEY_S)) players[0].rec.y += movementSpeed;

		if (IsKeyDown(KEY_UP)) players[1].rec.y -= movementSpeed;
		if (IsKeyDown(KEY_DOWN)) players[1].rec.y += movementSpeed;
		playerLimits();

		barrierShooting();


		//Init ball speed
		for (int i = 0; i < ballMax; i++)
		{
			if (balls[i].active == true) {
				balls[i].ballPosition.x += balls[i].ballSpeed.x;
				balls[i].ballPosition.y += balls[i].ballSpeed.y;
			}
		}

		collisions(counterBall, counterColor, background);

		//Goes to the end screen
		if (players[0].points >= win || players[1].points >= win) {
			endScreen();
		}
		drawObjects();
	}
}
void menu() {

	SetTargetFPS(60);

	initAudio();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Pong", GetScreenWidth() / 2 - 70, screenHeight / 2 - 200, 50, LIGHTGRAY);
		DrawText("(No apto para epilepticos)", GetScreenWidth() / 2 - 105, screenHeight / 2 - 140, 15, LIGHTGRAY);

		DrawText("Start", GetScreenWidth() / 2 - 150, screenHeight / 2, 20, LIGHTGRAY);
		DrawText("(Enter)", GetScreenWidth() / 2 - 160, screenHeight / 2 + 20, 20, LIGHTGRAY);

		DrawText("Exit", GetScreenWidth() / 2 + 70, screenHeight / 2, 20, LIGHTGRAY);
		DrawText("(Escape)", GetScreenWidth() / 2 + 45, screenHeight / 2 + 20, 20, LIGHTGRAY);

		DrawText("Space: player 1 skill", GetScreenWidth() / 2 - 230, screenHeight / 2 + 50, 20, LIGHTGRAY);
		DrawText("Right Ctrl: player 2 skill", GetScreenWidth() / 2 - 10, screenHeight / 2 + 50, 20, LIGHTGRAY);

		if (IsKeyPressed(KEY_ENTER)) game();

		EndDrawing();
	}
}
static void drawObjects() {

	BeginDrawing();

	//Draws all balls
	for (int i = 0; i < ballMax; i++)
	{
		if (balls[i].active == true)
			DrawCircleV(balls[i].ballPosition, 10, players[0].playerColor);
	}

	//Draws players and barriers
	for (int i = 0; i < playerMax; i++)
	{
		DrawRectangleRec(players[i].rec, players[i].playerColor);
		if (barriers[i].active == true)
		{
			DrawRectangleRec(barriers[i].rec, players[i].playerColor);
		}
	}

	//Draws points
	DrawText(FormatText("%i", players[0].points), 340, 200, 50, players[0].playerColor);
	DrawText(FormatText("%i", players[1].points), 425, 200, 50, players[1].playerColor);

	EndDrawing();
}
static void endScreen() {

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		if (players[0].points >= win) {
			DrawText(FormatText("Ganador: Jugador 1: %i puntos", players[0].points), GetScreenWidth() / 2 - 150, screenHeight / 2 - 50, 20, BLACK);
			DrawText(FormatText("Pededor: Jugador 2: %i puntos", players[1].points), GetScreenWidth() / 2 - 150, screenHeight / 2, 20, BLACK);
		}

		if (players[1].points >= win) {
			DrawText(FormatText("Ganador: Jugador 2: %i puntos", players[1].points), GetScreenWidth() / 2 - 150, screenHeight / 2 - 50, 20, BLACK);
			DrawText(FormatText("Perdedor: Jugador 1: %i puntos", players[0].points), GetScreenWidth() / 2 - 150, screenHeight / 2, 20, BLACK);
		}

		DrawText("Presione Enter para volver a jugar.", GetScreenWidth() / 2 - 150, screenHeight / 2 + 50, 20, BLACK);

		if (IsKeyPressed(KEY_ENTER)) {
			players[0].points = 0;
			players[1].points = 0;
			game();
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
}
static void collisions(int &counterBall, int &counterColor, Color &background) {
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
			getPowerUp(1);
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
			getPowerUp(0);
			if (i % 2 == 0)
				balls[i].ballPosition.x *= 1.5f;
			else
				balls[i].ballPosition.y *= 1.5f;

			balls[i].ballPosition = ballPositionInit;
			changeColor(counterColor, background);
		}
	}
}

static void playerLimits()
{
	for (int i = 0; i < playerMax; i++)
	{
		if (players[i].rec.y > screenHeight - players[i].rec.height)
			players[i].rec.y = screenHeight - players[i].rec.height;
		if (players[i].rec.y < 0)
			players[i].rec.y = 0;
	}
}

static void barrierShooting() {
	barriers[0].rec.y == players[0].rec.y;
	barriers[1].rec.y == players[1].rec.y;
	if (IsKeyPressed(KEY_SPACE)) {
		barriers[0].active = true;
	}
	if (barriers[0].active == true) {
		barriers[0].rec.x += 5;
	}
	if (barriers[0].rec.x > 390) {
		barriers[0].active = false;
	}
	if (barriers[0].active == false) {
		barriers[0].rec.x = players[0].rec.x + 10;
		barriers[0].rec.y = players[0].rec.y;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
		barriers[1].active = true;
	}
	if (barriers[1].active == true) {
		barriers[1].rec.x -= 5;
	}
	if (barriers[1].rec.x < 400) {
		barriers[1].active = false;
	}
	if (barriers[1].active == false) {
		barriers[1].rec.x = players[1].rec.x;
		barriers[1].rec.y = players[1].rec.y;
	}
}

static void getPowerUp(int whichPlayer) {
	players[whichPlayer].rec.height += 1.0f;
	barriers[whichPlayer].rec.height += 1.0f;
}

static void multiplyBall(int &counterBall) {
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

static void changeColor(int &counterColor, Color &background) {
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