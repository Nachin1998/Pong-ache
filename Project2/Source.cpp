#include "Headers.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int playerMax = 2;
const int ballMax = 10;
const int powerUpMax = 20;
const int win = 100;
const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
Music music;

struct players {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	int points;
	int ammo;
	bool haveAmmo;
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
	int radius;
	bool active;
}ball[ballMax];


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

		DrawText("Space: player 1 skill", screenWidth / 2 - 230, screenHeight / 2 + 50, 20, LIGHTGRAY);
		DrawText("Right Ctrl: player 2 skill", screenWidth / 2 - 10, screenHeight / 2 + 50, 20, LIGHTGRAY);

		if (IsKeyPressed(KEY_ENTER)) game();

		EndDrawing();
	}
}

void game() {
	
	music = LoadMusicStream("Audio/Megalovania.ogg");

	PlayMusicStream(music);

	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counterBall = 0;
	Vector2 size = { 18.0f, 120.0f };

	//Players
	for (int i = 0; i < playerMax; i++)
	{
		player[i].rec.y = screenHeight / 2;
		player[i].rec.width = size.x;
		player[i].rec.height = size.y;
		player[i].size = size;
		player[i].points = 0;
		player[i].ammo = 0;
		player[i].haveAmmo = false;
		player[i].playerColor = WHITE;
	}
	player[0].rec.x = screenWidth - screenWidth + 30;
	player[1].rec.x = screenWidth - 50;

	//Barriers
	for (int i = 0; i < playerMax; i++)
	{
		barrier[i].rec.width = size.x/3;
		barrier[i].rec.height = size.y;
		barrier[i].size = size;
		barrier[i].active = false;	
	}
	
	//Balls
	for (int i = 0; i < ballMax; i++)
	{
		ball[i].ballPosition = ballPositionInit;
		ball[i].ballSpeed.x = 5.0f;
		ball[i].ballSpeed.y = 5.0f;
		ball[i].radius = 5;
		ball[i].active = false;
	}
	ball[0].active = true;
	
	SetTargetFPS(60);
	getPowerUp(1);
	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);

		ClearBackground(background);

		if (IsKeyDown(KEY_W)) player[0].rec.y -= 6.0f;
		if (IsKeyDown(KEY_S)) player[0].rec.y += 6.0f;

		if (IsKeyDown(KEY_UP)) player[1].rec.y -= 6.0f;
		if (IsKeyDown(KEY_DOWN)) player[1].rec.y += 6.0f;
		playerLimits();

		barrierShooting();
		

		//Init ball speed
		for (int i = 0; i < ballMax; i++)
		{
			if (ball[i].active == true) {
				ball[i].ballPosition.x += ball[i].ballSpeed.x;
				ball[i].ballPosition.y += ball[i].ballSpeed.y;
			}
		}
		
		collisions(counterBall, counterColor, background);
		
		//Goes to the end screen
		if (player[0].points >= win || player[1].points >= win) {
			endScreen();
		}
		drawObjects();
	}
}

void drawObjects() {

	BeginDrawing();

	//Draws all balls
	for (int i = 0; i < ballMax; i++)
	{
		if (ball[i].active == true)
			DrawCircleV(ball[i].ballPosition, 10, player[0].playerColor);
	}
		
	//Draws players and barriers
	for (int i = 0; i < playerMax; i++)
	{
		DrawRectangleRec(player[i].rec, player[i].playerColor);
		if (barrier[i].active == true)
		{
			DrawRectangleRec(barrier[i].rec, player[i].playerColor);
		}
	}
	
	//Draws points
	DrawText(FormatText("%i", player[0].points), 340, 200, 50, player[0].playerColor);
	DrawText(FormatText("%i", player[1].points), 425, 200, 50, player[1].playerColor);

	EndDrawing();
}

void collisions(int &counterBall, int &counterColor, Color &background) {
	for (int i = 0; i < ballMax; i++)
	{
		//Detects the colision with players and changes the color
		if (CheckCollisionCircleRec(ball[i].ballPosition, ball[i].radius, player[0].rec) ||
			CheckCollisionCircleRec(ball[i].ballPosition, ball[i].radius, player[1].rec)) {

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

		//Detects the colision with shot barriers and changes the color
		if (CheckCollisionCircleRec(ball[i].ballPosition, ball[i].radius, barrier[0].rec) ||
			CheckCollisionCircleRec(ball[i].ballPosition, ball[i].radius, barrier[1].rec)) {
			ball[i].ballSpeed.x *= -1.0f;
			multiplyBall(counterBall);
			if (ball[i].ballSpeed.x < 0) {
				ball[i].ballPosition.x -= 15.0f;
				changeColor(counterColor, background);
			}
			else {
				ball[i].ballPosition.x += 15;
				changeColor(counterColor, background);
			}
		}

		//Detects the colision with walls and changes the color
		if ((ball[i].ballPosition.y >= (GetScreenHeight() - ball[i].radius)) || (ball[i].ballPosition.y <= ball[i].radius)) {
			ball[i].ballSpeed.y *= -1.0f;
			changeColor(counterColor, background);
		}

		//Detects the colision with the left scoring wall
		if (ball[i].ballPosition.x <= 0) {
			player[1].points++;
			ball[i].ballPosition = ballPositionInit;
			changeColor(counterColor, background);
		}

		//Detects the colision with the right scoring wall
		if (ball[i].ballPosition.x >= GetScreenWidth()) {
			player[0].points++;
			ball[i].ballPosition.x *= 1.5f;
			ball[i].ballPosition = ballPositionInit;
			changeColor(counterColor, background);
		}
	}
}

void playerLimits()
 {
	for (int i = 0; i < playerMax; i++)
	{
		if (player[i].rec.y > screenHeight - player[i].rec.height)
			player[i].rec.y = screenHeight - player[i].rec.height;
		if (player[i].rec.y < 0)
			player[i].rec.y = 0;
	}
}

void barrierShooting() {
	barrier[0].rec.y == player[0].rec.y;
	barrier[1].rec.y == player[1].rec.y;
	if (IsKeyPressed(KEY_SPACE)) {
		barrier[0].active = true;
	}
	if (barrier[0].active == true) {
		barrier[0].rec.x += 5;
	}
	if (barrier[0].rec.x > 390) {
		barrier[0].active = false;
	}
	if (barrier[0].active == false) {
		barrier[0].rec.x = player[0].rec.x + 10;
		barrier[0].rec.y = player[0].rec.y;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
		barrier[1].active = true;
	}
	if (barrier[1].active == true) {
		barrier[1].rec.x -= 5;
	}
	if (barrier[1].rec.x < 400) {
		barrier[1].active = false;
	}
	if (barrier[1].active == false) {
		barrier[1].rec.x = player[1].rec.x;
		barrier[1].rec.y = player[1].rec.y;
	}
}

void getPowerUp() {
	for (int i = 0; i < playerMax; i++)
	{
		float sizeMax = player[i].rec.height+10;
		int pointsMax = player[i].points + 10;
		if (pointsMax == player[i].points) {
			sizeMax += 5;
			pointsMax += 10;
		}
		if (sizeMax>player[i].rec.height)
		{
			player[i].rec.height += 50;
			barrier[i].rec.height += 50;
		}
	}
}

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

void main()
{
	InitWindow(screenWidth, screenHeight, "Pongacho");
	menu();
	CloseWindow();
}