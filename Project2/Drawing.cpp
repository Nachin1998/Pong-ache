#include "Drawing.h"

#include "Players.h"
#include "Barriers.h"
#include "Balls.h"

namespace Ignacio {
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
}