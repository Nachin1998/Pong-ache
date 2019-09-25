#include "Barriers.h"
#include "gameManager.h"
Barrier barriers[barrierMax];

void setBarrierParameters() {
	for (int i = 0; i < barrierMax; i++)
	{
		barriers[i].rec.width = size.x / 3;
		barriers[i].rec.height = size.y;
		barriers[i].size = size;
		barriers[i].active = false;
	}
}
