#include "game.h"
#include "gameManager.h"

void game() {

	PlayMusicStream(gameMusic);

	Color background = BLACK;
	int counterColor = 0;
	int counterTiempo = 0;
	int counterBall = 0;

	setAllParameters();

	SetTargetFPS(60);

	// Main game loop
	while (!WindowShouldClose())
	{
		UpdateMusicStream(gameMusic);

		ClearBackground(background);

		inputs();
		playerLimits();
		barrierShooting();
		initBallSpeed();

		collisions(counterBall, counterColor, background);

		//Goes to the end screen
		if (players[0].points >= win || players[1].points >= win) {
			endScreen();
		}
		drawObjects();
	}
}