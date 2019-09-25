#include "Headers.h"
#include "Players.h"
//MULTIPLICAR VARIABLES POR  * GetFrameTime() 


const int screenWidth = 800;
const int screenHeight = 450;
const int ballMax = 15;
const int powerUpMax = 20;
const int movementSpeed = 6;
const int win = 100;
const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
Music music;

float timer = 0.0;

struct Barrier {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
	bool active;
}barriers[playerMax];

struct Ball {
	Vector2 ballSpeed;
	Vector2 ballPosition;
	int radius;
	bool active;
}balls[ballMax];

struct PowerUps {
	Rectangle rec;
	Vector2 size;
	Color powerUpColor;
	bool active;
}powerUp;

void endScreen() {

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

void menu() {

	SetTargetFPS(60);

	InitAudioDevice();

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

void game() {
	
	music = LoadMusicStream("Audio/Megalovania.ogg");

	PlayMusicStream(music);

	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counterBall = 0;

	//Players
	for (int i = 0; i < playerMax; i++)
	{
		players[i].rec.y = screenHeight / 2;
		players[i].rec.width = size.x;
		players[i].rec.height = size.y;
		players[i].size = size;
		players[i].points = 0;
		players[i].playerColor = WHITE;
	}
	players[0].rec.x = GetScreenWidth() - GetScreenWidth() + 30;
	players[1].rec.x = GetScreenWidth() - 50;

	//Barriers
	for (int i = 0; i < playerMax; i++)
	{
		barriers[i].rec.width = size.x/3;
		barriers[i].rec.height = size.y;
		barriers[i].size = size;
		barriers[i].active = false;	
	}
	
	//Balls
	for (int i = 0; i < ballMax; i++)
	{
		balls[i].ballPosition = ballPositionInit;
		balls[i].ballSpeed.x = 5.0f;
		balls[i].ballSpeed.y = 5.0f;
		balls[i].radius = 5;
		balls[i].active = false;
	}
	balls[0].active = true;


	powerUp.rec.y = screenHeight / 2;
	powerUp.rec.x = GetScreenWidth() / 2;
	powerUp.rec.width = 10;
	powerUp.rec.height = 10;
	powerUp.size = size;
	powerUp.powerUpColor = players[0].playerColor;
	powerUp.active = false;
	

	//SetTargetFPS(60);
	
	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);

		ClearBackground(background);

		if (IsKeyDown(KEY_W)) players[0].rec.y -= movementSpeed;
		if (IsKeyDown(KEY_S)) players[0].rec.y += movementSpeed;

		if (IsKeyDown(KEY_UP)) players[1].rec.y -= movementSpeed;
		if (IsKeyDown(KEY_DOWN)) players[1].rec.y += movementSpeed;
		playerLimits();

		barrierShooting();
		
		timer += GetFrameTime();

		
		if (timer > 1.0f) {
			powerUp.active = true;
			timer = 0.0f;
		}
		
		
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

void drawObjects() {

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
			getPowerUp(1);
			balls[i].ballPosition.x *= 1.5f;
			balls[i].ballPosition = ballPositionInit;
			changeColor(counterColor, background);
		}

		//Detects the colision with the left scoring wall
		if (balls[i].ballPosition.x <= 0) {
			players[1].points++;
			getPowerUp(0);
			balls[i].ballPosition = ballPositionInit;
			changeColor(counterColor, background);
		}
	}
}

void playerLimits()
 {
	for (int i = 0; i < playerMax; i++)
	{
		if (players[i].rec.y > screenHeight - players[i].rec.height)
			players[i].rec.y = screenHeight - players[i].rec.height;
		if (players[i].rec.y < 0)
			players[i].rec.y = 0;
	}
}

void barrierShooting() {
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

void getPowerUp(int whichPlayer) {
	players[whichPlayer].rec.height += 1.0f;
	barriers[whichPlayer].rec.height += 1.0f;
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
			
		}
	}
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

void main()
{
	InitWindow(screenWidth, screenHeight, "We're grooovin");
	menu();
	CloseWindow();
}