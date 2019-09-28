#pragma once
#include "raylib.h"
#include "Players.h" 
#include "Barriers.h" 
#include "Balls.h" 
#include "Audio.h"
#include "Drawing.h"
#include "mainMenu.h"
#include "game.h"
#include "endScreen.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int powerUpMax = 20;
const int movementSpeed = 6;
const int win = 10;
const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
const Vector2 size= { 18.0f, 120.0f };

extern Color background;
extern int counterColor;
extern int counterTiempo;
extern int counterBall;

void play();

void update();
void collisions(int &counterBall, int &counterColor, Color &background);
void setAllParameters();
void inputs();

void getSizeUp(int whichPlayer);
void changeColor(int &counterColor, Color &background);