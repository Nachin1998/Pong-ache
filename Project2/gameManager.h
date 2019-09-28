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

#include "inputs.h"
#include "collisions.h"
#include "changeColor.h"
#include "getSizeUp.h"

namespace Ignacio {
	const int screenWidth = 800;
	const int screenHeight = 450;
	const int powerUpMax = 20;
	const int movementSpeed = 300;
	const int win = 100;
	const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
	const Vector2 size = { 18.0f, 120.0f };

	extern Color background;
	extern int counterColor;
	extern int counterTiempo;
	extern int counterBall;

	void play();

	void setAllParameters();
	void inputs();
	void update();
}
#endif