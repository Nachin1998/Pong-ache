#include "Barriers.h"
#include "entities/players/Players.h"

#include "game_manager/variables.h"

namespace IgnacioFernandezLemos {

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
	void barrierShooting() {

		if (IsKeyPressed(KEY_SPACE)) {
			barriers[0].active = true;
		}
		if (barriers[0].active == true) {
			barriers[0].rec.x += 280 * GetFrameTime();;
		}
		if (barriers[0].rec.x > 390) {
			barriers[0].active = false;
		}
		if (barriers[0].active == false) {
			barriers[0].rec.x = players[0].rec.x + 10;
			barriers[0].rec.y = players[0].rec.y;
		}

		if (IsKeyPressed(KEY_RIGHT_CONTROL)) {
			barriers[1].active = true;
		}
		if (barriers[1].active == true) {
			barriers[1].rec.x -= 280 * GetFrameTime();;
		}
		if (barriers[1].rec.x < 400) {
			barriers[1].active = false;
		}
		if (barriers[1].active == false) {
			barriers[1].rec.x = players[1].rec.x;
			barriers[1].rec.y = players[1].rec.y;
		}
	}
}