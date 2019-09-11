#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 450;

Rectangle player1Barrier;
Rectangle player2Barrier;

void juego();
struct players {
	Rectangle rec;
	Vector2 size;
	Color playerColor;
}player[2];

struct ball {
	float speed;
	float radius;
	int points;
	bool active;
}balls[30];

Music music;

/*void multiplyBall(Vector2 ballPosition,Vector2 ballSpeed,Color playerColor) {
	
}*/

void cambiarColor(int &counterColor, Color &playerColor, Color &background) {
	if (counterColor % 2 == 0) {
		playerColor = BLACK;
		background = WHITE;
	}
	else {
		playerColor = WHITE;
		background = BLACK;
	}
	if (counterColor >= 1) {
		counterColor = 0 - 1;
	}
	counterColor++;
}
/*cambiarColor(counter, playerColor, background);*/

void endScreen(const int screenWidth, const int screenHeight, int points1, int points2) {

	CloseAudioDevice();

	while (!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(WHITE);

		if (points1 == 5) {
			DrawText(FormatText("Ganador: Jugador 1: %i puntos", points1), screenWidth / 2-150, screenHeight / 2-50, 20, BLACK);
			DrawText(FormatText("Pededor: Jugador 2: %i puntos", points2), screenWidth / 2 - 150, screenHeight / 2, 20, BLACK);
		}
		
		if (points2 == 5) {
			DrawText(FormatText("Ganador: Jugador 2: %i puntos", points2), screenWidth/ 2 - 150, screenHeight / 2-50, 20, BLACK);
			DrawText(FormatText("Perdedor: Jugador 1: %i puntos", points1), screenWidth / 2 - 150, screenHeight / 2, 20, BLACK);
		}

		DrawText("Presione Enter para volver a jugar.", screenWidth / 2 - 150, screenHeight / 2+50, 20, BLACK);

		if (IsKeyPressed(KEY_ENTER)) {
			points1 = 0;
			points2 = 0;
			juego();
		}
		EndDrawing();
		//----------------------------------------------------------------------------------
	}
}

void menu() {

	SetTargetFPS(60);

	InitAudioDevice();              // Initialize audio device

	music = LoadMusicStream("Audio/Megalovania.ogg");

	PlayMusicStream(music);

	while (!WindowShouldClose())
	{
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Pong", screenWidth/2-70, screenHeight/2-200, 50, LIGHTGRAY);
		DrawText("(No apto para epilepticos)", screenWidth/2-105, screenHeight/2-140, 15, LIGHTGRAY);

		DrawText("Start", screenWidth/2-150, screenHeight/2, 20, LIGHTGRAY);
		DrawText("(Enter)", screenWidth/2-160, screenHeight/2+20, 20, LIGHTGRAY);

		DrawText("Exit", screenWidth/2+70, screenHeight/2, 20, LIGHTGRAY);
		DrawText("(Escape)", screenWidth/2+45, screenHeight/2+20, 20, LIGHTGRAY);

		DrawText("Space para el player 1", screenWidth/2-250, screenHeight/2+50, 20, LIGHTGRAY);
		DrawText("Right Ctrl para el player 2", screenWidth / 2 + 20, screenHeight / 2 + 50, 20, LIGHTGRAY);

		if (IsKeyPressed(KEY_ENTER)) juego();

		EndDrawing();
	}
}

void juego() {

	float ballSpeedX = 6.5f;
	float ballSpeedY = 6.5f;
	Vector2 ballSpeed = { ballSpeedX, ballSpeedY };
	int ballRadius = 5;
	Color playerColor = WHITE;
	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counter = 0;
	int points1 = 0;
	int points2 = 0;
	int timer = 60;
	int fps = 60;
	bool activeBarrier1 = false;
	bool activeBarrier2 = false;
	bool newBall[50];


	//Players and balls
	Vector2 playerSize = { (float)18, (float)120 };
	Vector2 barrierSize = { (float)8, (float)120 };
	Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
	Vector2 ballPosition = ballPositionInit;
	
	//Barriers
	player1Barrier.x = player[0].rec.x+5;
	player1Barrier.y = player[0].rec.y;
	player1Barrier.width = barrierSize.x;
	player1Barrier.height = barrierSize.y;
	player2Barrier.x = player[0].rec.x;
	player2Barrier.y = player[1].rec.y;
	player2Barrier.width = barrierSize.x;
	player2Barrier.height = barrierSize.y;

	for (int i = 0; i < 2; i++)
	{
		player[i].rec.y= screenHeight / 2;
		player[i].rec.width = playerSize.x;
		player[i].rec.height = playerSize.y;
		player[i].size = playerSize;
	}
		player[0].rec.x = screenWidth - screenWidth + 30;
		player[1].rec.x = screenWidth - 50;

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(music);
		// Update
		//----------------------------------------------------------------------------------

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

		player1Barrier.y == player[0].rec.y;
		player2Barrier.y == player[1].rec.y;

		ballPosition.x += ballSpeed.x;
		ballPosition.y += ballSpeed.y;

		// Check walls collision for bouncing and changes color

		if (ballPosition.x >= GetScreenWidth()) {
			ballPosition = ballPositionInit;
			points1++;

			activeBarrier1 = false;
			activeBarrier2 = false;
			player1Barrier.x = player[0].rec.x;
			player1Barrier.y = player[0].rec.y;
			player2Barrier.x = player[1].rec.x;
			player2Barrier.y = player[1].rec.y;

			cambiarColor(counter, playerColor, background);
		}

		if (ballPosition.x <= 0) {
			ballPosition = ballPositionInit;
			points2++;
			player2Barrier.x = player[1].rec.x;
			player2Barrier.y = player[1].rec.y;
			cambiarColor(counter, playerColor, background);
		}

		//Detects the colision and changes the color
		if ((ballPosition.y >= (GetScreenHeight() - ballRadius)) || (ballPosition.y <= ballRadius)) {
			ballSpeed.y *= -1.0f;
			cambiarColor(counter, playerColor, background);
		}

		//Detects the colision and changes the color
		if (CheckCollisionCircleRec(ballPosition, ballRadius, player[0].rec) ||
			CheckCollisionCircleRec(ballPosition, ballRadius, player[1].rec)) {
			DrawCircleV(ballPositionInit, 100, playerColor);
			ballSpeed.x *= -1.0f;
			if (ballSpeed.x < 0) {
				ballPosition.x -= 15;
				cambiarColor(counter, playerColor, background);
			}
			else {
				ballPosition.x += 15;
				cambiarColor(counter, playerColor, background);
			}
		}

		if (points1 >= 50 || points2 >= 50) {
			endScreen(screenWidth, screenHeight, points1, points2);
		}

		// Draw
		BeginDrawing();

		ClearBackground(background);

		DrawText(FormatText("%i", points2), 420, 200, 50, playerColor);
		DrawText(FormatText("%i", points1), 340, 200, 50, playerColor);
		DrawCircleV(ballPosition, 10, playerColor);
		DrawRectangleRec(player[0].rec, playerColor);
		DrawRectangleRec(player[1].rec, playerColor);

		if (CheckCollisionCircleRec(ballPosition, ballRadius, player1Barrier) ||
			CheckCollisionCircleRec(ballPosition, ballRadius, player2Barrier)) {
			counter++;			
			cambiarColor(counter, playerColor, background);
			//multiplyBall(ballPosition, ballSpeed, playerColor);
		}

		if (IsKeyPressed(KEY_SPACE)) {
			activeBarrier1 = true;
		}

		if (activeBarrier1 == true) {
			if (IsKeyUp(KEY_SPACE)) {

				DrawRectangleRec(player1Barrier, playerColor);
				player1Barrier.x += 5;

				if (CheckCollisionCircleRec(ballPosition, ballRadius, player1Barrier))
				{
					ballSpeed.x *= -1.0f;
					if (ballSpeed.x < 0) {
						ballPosition.x -= 15;

						cambiarColor(counter, playerColor, background);
					}
					else {
						ballPosition.x += 15;

						cambiarColor(counter, playerColor, background);
					}

				}
				
				if (player1Barrier.x > 390) {
					activeBarrier1 = false;
				}
			}
		}
		else
			if (IsKeyUp(KEY_SPACE)) {
				player1Barrier.x = player[0].rec.x;
				player1Barrier.y = player[0].rec.y;
			}

		if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
			activeBarrier2 = true;
		}

		if (activeBarrier2 == true) {
			if (IsKeyUp(KEY_RIGHT_CONTROL)) {

				DrawRectangleRec(player2Barrier, playerColor);
				player2Barrier.x -= 5;

				if (CheckCollisionCircleRec(ballPosition, ballRadius, player2Barrier))
				{
					ballSpeed.x *= -1.0f;
					if (ballSpeed.x < 0) {
						ballPosition.x -= 15;

						cambiarColor(counter, playerColor, background);
					}
					else {
						ballPosition.x += 15;

						cambiarColor(counter, playerColor, background);
					}

				}
				
				if (player2Barrier.x < 400) {
					activeBarrier2 = false;
				}
			}
		}
		else
			if (IsKeyUp(KEY_SPACE)) {
				player2Barrier.x = player[1].rec.x;
				player2Barrier.y = player[1].rec.y;
			}

		EndDrawing();
	}
}

int main(void)
{
	InitWindow(screenWidth, screenHeight, "Pongacho");
	menu();
	CloseWindow();
}