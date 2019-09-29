#include "Players.h"
#include "variables.h"

namespace Ignacio {
	Player players[playerMax];

	void setPlayerParameters() {
		for (int i = 0; i < playerMax; i++)
		{
			players[i].rec.y = GetScreenHeight() / 2;
			players[i].rec.width = size.x;
			players[i].rec.height = size.y;
			players[i].size = size;
			players[i].points = 0;
			players[i].playerColor = WHITE;
		}
		players[0].rec.x = GetScreenWidth() - GetScreenWidth() + 30;
		players[1].rec.x = GetScreenWidth() - 50;
	}

	void playerLimits() {
		for (int i = 0; i < playerMax; i++)
		{
			if (players[i].rec.y > screenHeight - players[i].rec.height)
				players[i].rec.y = screenHeight - players[i].rec.height;
			if (players[i].rec.y < 0)
				players[i].rec.y = 0;
		}
	}
}