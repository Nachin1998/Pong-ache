#include "gameManager.h"

namespace IgnacioFernandezLemos {
	void play() {
		InitWindow(screenWidth, screenHeight, "Pongacho");
		update();
		CloseWindow();
	}

	void setAllParameters() {
		//Players
		setPlayerParameters();

		//Barriers
		setBarrierParameters();

		//Balls
		setBallParameters();
	}

	void update() {
		menu();
	}
}