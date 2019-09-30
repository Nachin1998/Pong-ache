#ifndef PLAYERS_H
#define PLAYERS_H

#include "raylib.h"

namespace IgnacioFernandezLemos {
	const int playerMax = 2;

	struct Player {
		Rectangle rec;
		Vector2 size;
		Color playerColor;
		int points;
	};

	extern Player players[playerMax];
	void setPlayerParameters();
	void playerLimits();
}

#endif