#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int playerMax = 2;
const int ballMax = 20;
const int win = 300;

void game();

struct players {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	int points;
}player[playerMax];

struct barriers {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	bool active;
}barrier[playerMax];

struct balls {
	Vector2 ballSpeed;
	Vector2 ballPosition;
	bool active;
}ball[ballMax];

Music music;

void multiplyBall(int &counterBall) {
	counterBall++;

	if (counterBall <= ballMax) {
		ball[counterBall].active = true;
	}

	for (int i = counterBall; i < ballMax; i++)
	{
		if (ball[i].active == true) {
			ball[i].ballPosition = ball[0].ballPosition;
			if (i % 2 == 0)
				ball[i].ballSpeed.x *= -1.1f;
			else
				ball[i].ballSpeed.y *= -1.1f;
		}
	}
}

void changeColor(int &counterColor, Color &background) {
	if (counterColor % 2 == 0) {
		player[0].playerColor = BLACK;
		player[1].playerColor = BLACK;
		background = WHITE;
	}
	else {
		player[0].playerColor = WHITE;
		player[1].playerColor = WHITE;
		background = BLACK;
	}
	if (counterColor >= 1) {
		counterColor = 0 - 1;
	}
	counterColor++;
}

void endScreen() {

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		if (player[0].points >= win) {
			DrawText(FormatText("Ganador: Jugador 1: %i puntos", player[0].points), screenWidth / 2 - 150, screenHeight / 2 - 50, 20, BLACK);
			DrawText(FormatText("Pededor: Jugador 2: %i puntos", player[1].points), screenWidth / 2 - 150, screenHeight / 2, 20, BLACK);
		}

		if (player[1].points >= win) {
			DrawText(FormatText("Ganador: Jugador 2: %i puntos", player[1].points), screenWidth / 2 - 150, screenHeight / 2 - 50, 20, BLACK);
			DrawText(FormatText("Perdedor: Jugador 1: %i puntos", player[0].points), screenWidth / 2 - 150, screenHeight / 2, 20, BLACK);
		}

		DrawText("Presione Enter para volver a jugar.", screenWidth / 2 - 150, screenHeight / 2 + 50, 20, BLACK);

		if (IsKeyPressed(KEY_ENTER)) {
			player[0].points = 0;
			player[1].points = 0;
			game();
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
}

void menu() {

	SetTargetFPS(60);

	InitAudioDevice();

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Pong", screenWidth / 2 - 70, screenHeight / 2 - 200, 50, LIGHTGRAY);
		DrawText("(No apto para epilepticos)", screenWidth / 2 - 105, screenHeight / 2 - 140, 15, LIGHTGRAY);

		DrawText("Start", screenWidth / 2 - 150, screenHeight / 2, 20, LIGHTGRAY);
		DrawText("(Enter)", screenWidth / 2 - 160, screenHeight / 2 + 20, 20, LIGHTGRAY);

		DrawText("Exit", screenWidth / 2 + 70, screenHeight / 2, 20, LIGHTGRAY);
		DrawText("(Escape)", screenWidth / 2 + 45, screenHeight / 2 + 20, 20, LIGHTGRAY);

		DrawText("Space para el player 1", screenWidth / 2 - 250, screenHeight / 2 + 50, 20, LIGHTGRAY);
		DrawText("Right Ctrl para el player 2", screenWidth / 2 + 20, screenHeight / 2 + 50, 20, LIGHTGRAY);

		if (IsKeyPressed(KEY_ENTER)) game();

		EndDrawing();
	}
}

void game() {
	//music = LoadMusicStream("Audio/Megalovania.ogg");

	PlayMusicStream(music);

	int ballRadius = 5;
	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counterBall = 0;

	//Balls
	Vector2 playerSize = { (float)18, (float)120 };
	Vector2 barrierSize = { (float)8, (float)120 };
	Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };

	//Players
	for (int i = 0; i < playerMax; i++)
	{
		player[i].rec.y = screenHeight / 2;
		player[i].rec.width = playerSize.x;
		player[i].rec.height = playerSize.y;
		player[i].size = playerSize;
		player[i].points = 0;
		player[i].playerColor = WHITE;
	}
	player[0].rec.x = screenWidth - screenWidth + 30;
	player[1].rec.x = screenWidth - 50;

	//Barriers
	for (int i = 0; i < playerMax; i++)
	{
		barrier[i].rec.y = player[i].rec.y;
		barrier[i].rec.width = barrierSize.x;
		barrier[i].rec.height = barrierSize.y;
		barrier[i].size = barrierSize;
		barrier[i].active = false;
	}
	barrier[0].rec.x = player[0].rec.x + 5;
	barrier[1].rec.x = player[0].rec.x;

	//Balls
	for (int i = 0; i < ballMax; i++)
	{
		ball[i].ballPosition = ballPositionInit;
		ball[i].ballSpeed.x = 5.0f;
		ball[i].ballSpeed.y = 5.0f;
		ball[i].active = false;
	}
	ball[0].active = true;

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);

		if (IsKeyDown(KEY_W)) player[0].rec.y -= 6.0f;
		if (IsKeyDown(KEY_S)) player[0].rec.y += 6.0f;
		if (player[0].rec.y > screenHeight - 120) {
			player[0].rec.y = screenHeight - 120;
		}
		if (player[0].rec.y < 0) {
			player[0].rec.y = 0;
		}

		if (IsKeyDown(KEY_UP)) player[1].rec.y -= 6.0f;
		if (IsKeyDown(KEY_DOWN)) player[1].rec.y += 6.0f;
		if (player[1].rec.y > screenHeight - 120)
			player[1].rec.y = screenHeight - 120;
		if (player[1].rec.y < 0)
			player[1].rec.y = 0;

		barrier[0].rec.y == player[0].rec.y;
		barrier[1].rec.y == player[1].rec.y;

		//Init ball speed
		for (int i = 0; i < ballMax; i++)
		{
			if (ball[i].active == true) {
				ball[i].ballPosition.x += ball[i].ballSpeed.x;
				ball[i].ballPosition.y += ball[i].ballSpeed.y;
			}
		}

		// Check walls collision for bouncing and changes color
		for (int i = 0; i < ballMax; i++)
		{
			if (ball[i].ballPosition.x >= GetScreenWidth()) {
				ball[i].ballPosition = ballPositionInit;
				player[0].points++;
				changeColor(counterColor, background);
			}
		}
		//Detects the colision the scoring wall
		for (int i = 0; i < ballMax; i++)
		{
			if (ball[i].ballPosition.x <= 0) {
				ball[i].ballPosition = ballPositionInit;
				player[1].points++;
				changeColor(counterColor, background);
			}
		}

		//Detects the colision with walls and changes the color
		for (int i = 0; i < ballMax; i++)
		{
			if ((ball[i].ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ball[i].ballPosition.y <= ballRadius)) {
				ball[i].ballSpeed.y *= -1.0f;
				changeColor(counterColor, background);
			}
		}

		//Detects the colision with player and changes the color
		for (int i = 0; i < ballMax; i++)
		{
			if (CheckCollisionCircleRec(ball[i].ballPosition, ballRadius, player[0].rec) ||
				CheckCollisionCircleRec(ball[i].ballPosition, ballRadius, player[1].rec)) {

				ball[i].ballSpeed.x *= -1.0f;
				if (ball[i].ballSpeed.x < 0) {
					ball[i].ballPosition.x -= 15;
					changeColor(counterColor, background);
				}
				else {
					ball[i].ballPosition.x += 15;
					changeColor(counterColor, background);
				}
			}
		}
		

		if (player[0].points >= win || player[1].points >= win) {
			endScreen();
		}

		// Draw
		BeginDrawing();

		ClearBackground(background);

		DrawText(FormatText("%i", player[0].points), 340, 200, 50, player[0].playerColor);
		DrawText(FormatText("%i", player[1].points), 420, 200, 50, player[1].playerColor);
		for (int i = 0; i < ballMax; i++)
		{
			if (ball[i].active == true) 
				DrawCircleV(ball[i].ballPosition, 10, player[0].playerColor);
			
		}
		DrawRectangleRec(player[0].rec, player[0].playerColor);
		DrawRectangleRec(player[1].rec, player[1].playerColor);
		DrawRectangleRec(barrier[0].rec, player[0].playerColor);
		DrawRectangleRec(barrier[1].rec, player[0].playerColor);

		for (int i = 0; i < ballMax; i++)
		{
			if (CheckCollisionCircleRec(ball[i].ballPosition, ballRadius, barrier[0].rec) ||
				CheckCollisionCircleRec(ball[i].ballPosition, ballRadius, barrier[1].rec)) {
				ball[i].ballSpeed.x *= -1.0f;
				multiplyBall(counterBall);
				if (ball[i].ballSpeed.x < 0) {
					ball[i].ballPosition.x -= 15;
					changeColor(counterColor, background);
				}
				else {
					ball[i].ballPosition.x += 15;
					changeColor(counterColor, background);
				}
				
			}
		}

		if (IsKeyPressed(KEY_SPACE)) {
			barrier[0].active = true;
		}

		if (barrier[0].active == true) {
			if (IsKeyUp(KEY_SPACE)) {

				
				barrier[0].rec.x += 5;

				if (CheckCollisionCircleRec(ball[0].ballPosition, ballRadius, barrier[0].rec))
				{
					ball[0].ballSpeed.x *= -1.0f;
					if (ball[0].ballSpeed.x < 0) {
						ball[0].ballPosition.x -= 15;

						changeColor(counterColor, background);
					}
					else {
						ball[0].ballPosition.x += 15;

						changeColor(counterColor, background);
					}

				}

				if (barrier[0].rec.x > 390) {
					barrier[0].active = false;
				}
			}
		}
		else
			if (IsKeyUp(KEY_SPACE)) {
				barrier[0].rec.x = player[0].rec.x;
				barrier[0].rec.y = player[0].rec.y;
			}

		if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
			barrier[1].active = true;
		}

		if (barrier[1].active == true) {
			if (IsKeyUp(KEY_RIGHT_CONTROL)) {
				barrier[1].rec.x -= 5;

				if (CheckCollisionCircleRec(ball[0].ballPosition, ballRadius, barrier[1].rec))
				{
					ball[0].ballSpeed.x *= -1.0f;
					if (ball[0].ballSpeed.x < 0) {
						ball[0].ballPosition.x -= 15;
						changeColor(counterColor, background);
					}
					else {
						ball[0].ballPosition.x += 15;
						changeColor(counterColor, background);
					}

				}
				if (barrier[1].rec.x < 400) {
					barrier[1].active = false;
				}
			}
		}
		else
			if (IsKeyUp(KEY_SPACE)) {
				barrier[1].rec.x = player[1].rec.x;
				barrier[1].rec.y = player[1].rec.y;
			}
		EndDrawing();
	}
}

void main()
{
	InitWindow(screenWidth, screenHeight, "Pongacho");
	menu();
	CloseWindow();
}