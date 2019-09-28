#include "endScreen.h"
#include "gameManager.h"

namespace Ignacio {
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
		}
	}
}