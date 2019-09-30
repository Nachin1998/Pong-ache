#include "game.h"
#include "game_manager/gameManager.h"
#include "scenes/pause_menu/pauseMenu.h"

namespace IgnacioFernandezLemos {
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
			if(IsKeyReleased(KEY_P)) pauseMenu();
			
			collisions(counterBall, counterColor, background);

			//Goes to the end screen
			if (players[0].points >= win) {
				players[0].points = win;
				StopMusicStream(gameMusic);
				endScreen();
			}
			if (players[1].points >= win) {
				players[1].points = win;
				StopMusicStream(gameMusic);
				endScreen();
			}
			drawObjects();
		}
	}

	
}