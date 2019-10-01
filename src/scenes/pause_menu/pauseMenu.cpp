#include "pauseMenu.h"

#include "raylib.h"

#include "game_manager/variables.h"
#include "game_manager/gameManager.h"
#include <iostream>

namespace IgnacioFernandezLemos {

	void pauseMenu() {
	
		bool pause = true;

		while (pause)
		{
			BeginDrawing();

			ClearBackground(BLACK);

			DrawText("Pause", GetScreenWidth() / 2 - 350, screenHeight / 2 - 200, 50, LIGHTGRAY);

			DrawText("Press R to resume the game.", GetScreenWidth() / 2 - 350, screenHeight / 2 - 50, 20, LIGHTGRAY);
			DrawText("Press M to end the game.", GetScreenWidth() / 2 - 350, screenHeight / 2, 20, LIGHTGRAY);
			DrawText("Press E to exit the game.", GetScreenWidth() / 2 - 350, screenHeight / 2 + 50, 20, LIGHTGRAY);

			DrawText(FormatText("%i", players[0].points), GetScreenWidth() / 2 - 65, screenHeight / 2 + 150, 50, LIGHTGRAY);
			DrawText(FormatText("%i", players[1].points), GetScreenWidth() / 2 + 20, screenHeight / 2 + 150, 50, LIGHTGRAY);

			if (IsKeyPressed(KEY_R)) {
				pause = false;
			}
			if (IsKeyPressed(KEY_M)) {
				pause = false;
				endScreen();
			}
			if (IsKeyPressed(KEY_E)) {
				pause = false;
				exit(0);
			}

			EndDrawing();
		}
	}
}