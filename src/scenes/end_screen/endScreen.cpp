#include "endScreen.h"
#include "game_manager/gameManager.h"

namespace IgnacioFernandezLemos {
	void endScreen() {
		float timePlayed;

		PlayMusicStream(endScreenMusic);
		SetMusicLoopCount(endScreenMusic, 0);

		while (!WindowShouldClose())
		{

			UpdateMusicStream(endScreenMusic);

			timePlayed = GetMusicTimePlayed(endScreenMusic) / GetMusicTimeLength(endScreenMusic);

			if (timePlayed > 1) StopMusicStream(endScreenMusic);

			BeginDrawing();
			ClearBackground(WHITE);

			if (players[0].points >= win) {
				DrawText(FormatText("Winner: Player 1: %i points", players[0].points), GetScreenWidth() / 2 - 150, screenHeight / 2 - 130, 20, BLACK);
				DrawText(FormatText("Loser: Player 2: %i points", players[1].points), GetScreenWidth() / 2 - 150, screenHeight / 2 - 80, 20, BLACK);
			}

			if (players[1].points >= win) {
				DrawText(FormatText("Winner: Player 2: %i points", players[1].points), GetScreenWidth() / 2 - 150, screenHeight / 2 - 130, 20, BLACK);
				DrawText(FormatText("Loser: Player 1: %i points", players[0].points), GetScreenWidth() / 2 - 150, screenHeight / 2  - 80, 20, BLACK);
			}

			if (players[0].points < win && players[1].points < win) {
				DrawText("Press Enter to play again.", GetScreenWidth() / 2 - 220, screenHeight / 2 - 10, 30, BLACK);
				DrawText("Press Escape to leave the game.", GetScreenWidth() / 2 - 220, screenHeight / 2 - 50, 30, BLACK);
			}
			else {
				DrawText("Press Enter to play again.", GetScreenWidth() / 2 - 150, screenHeight / 2 + 50, 20, BLACK);
				DrawText("Press Escape to leave the game.", GetScreenWidth() / 2 - 150, screenHeight / 2 + 70, 20, BLACK);
			}
			if (IsKeyPressed(KEY_ENTER)) {
				players[0].points = 0;
				players[1].points = 0;
				closeAudio();
				game();
			}
			EndDrawing();
		}
	}
}