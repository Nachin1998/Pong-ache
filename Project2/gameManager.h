#pragma once
#include "raylib.h"
#include "Players.h" 
#include "Barriers.h" 
#include "Balls.h" 
//#include "Audio.h"

const int screenWidth = 800;
const int screenHeight = 450;
const int powerUpMax = 20;
const int movementSpeed = 6;
const int win = 10;
const Vector2 ballPositionInit = { (float)screenWidth / 2, (float)screenHeight / 2 };
extern Vector2 size;

void menu();
void game();
void endScreen();

void playerLimits();
static void collisions(int &counterBall, int &counterColor, Color &background);

void drawObjects();

void barrierShooting();
void getPowerUp(int whichPlayer);
void multiplyBall(int &counterBall);
void changeColor(int &counterColor, Color &background);