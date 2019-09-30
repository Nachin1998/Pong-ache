#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "entities/players/Players.h" 
#include "entities/barriers/Barriers.h" 
#include "entities/balls/Balls.h" 

#include "audio/Audio.h"
#include "drawing/Drawing.h"

#include "scenes/main _menu/mainMenu.h"
#include "scenes/game/game.h"
#include "scenes/end_screen/endScreen.h"
#include "scenes/pause_menu/pauseMenu.h"

#include "variables.h"
#include "game_logic/collisions/collisions.h"


namespace IgnacioFernandezLemos {

	void play();

	void setAllParameters();
	void inputs();
	void update();
}
#endif