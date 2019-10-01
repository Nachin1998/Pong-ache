#include "gameManager.h"

namespace IgnacioFernandezLemos {
	void play() {
		InitWindow(screenWidth, screenHeight, "Pwong");
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