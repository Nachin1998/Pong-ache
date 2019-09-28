#include "gameManager.h"
#include "raylib.h"

namespace Ignacio {
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
}