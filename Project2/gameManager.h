#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "Players.h" 
#include "Barriers.h" 
#include "Balls.h" 

#include "Audio.h"
#include "Drawing.h"

#include "mainMenu.h"
#include "game.h"
#include "endScreen.h"

#include "variables.h"
#include "collisions.h"


namespace Ignacio {

	void play();

	void setAllParameters();
	void inputs();
	void update();
}
#endif