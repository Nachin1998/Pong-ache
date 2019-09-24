#pragma once
void menu();
void game();
void endScreen();
void playerLimits();
void collisions(int &counterBall, int &counterColor, Color &background);
void barrierShooting();
void drawObjects();
void getPowerUp(int whichPlayer);
void multiplyBall(int &counterBall);
void changeColor(int &counterColor, Color &background);