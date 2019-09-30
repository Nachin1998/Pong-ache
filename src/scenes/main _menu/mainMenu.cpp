#include "game_manager/gameManager.h"

namespace IgnacioFernandezLemos {
	void menu() {

		SetTargetFPS(60);

		initAudio();

		while (!WindowShouldClose())
		{
			BeginDrawing();

			ClearBackground(BLACK);

			DrawText("Pong", GetScreenWidth() / 2 - 70, screenHeight / 2 - 200, 50, LIGHTGRAY);
			DrawText("(Epilepsy Warning)", GetScreenWidth() / 2 - 100, screenHeight / 2 - 140, 20, LIGHTGRAY);

			DrawText("Start", GetScreenWidth() / 2 - 180, screenHeight / 2 - 40, 20, LIGHTGRAY);
			DrawText("(Enter)", GetScreenWidth() / 2 - 190, screenHeight / 2 - 20, 20, LIGHTGRAY);

			DrawText("Exit", GetScreenWidth() / 2 + 120, screenHeight / 2 - 40, 20, LIGHTGRAY);
			DrawText("(Escape)", GetScreenWidth() / 2 + 94, screenHeight / 2 -20, 20, LIGHTGRAY);

			DrawText("Space: player 1 skill", GetScreenWidth() / 2 - 250, screenHeight / 2 + 50, 20, LIGHTGRAY);
			DrawText("Right Ctrl: player 2 skill", GetScreenWidth() / 2 + 25, screenHeight / 2 + 50, 20, LIGHTGRAY);

			DrawText("P to pause", GetScreenWidth() / 2 - 60, screenHeight / 2 +200, 20, LIGHTGRAY);

			if (IsKeyPressed(KEY_ENTER)) game();

			EndDrawing();
		}
	}
}