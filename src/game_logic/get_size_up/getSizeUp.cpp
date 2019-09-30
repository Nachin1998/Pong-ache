#include "getSizeUp.h"

#include "entities/players/Players.h"
#include "entities/barriers/Barriers.h"

namespace IgnacioFernandezLemos {
	void getSizeUp(int whichPlayer) {
		players[whichPlayer].rec.height += 45.0f * GetFrameTime();
		barriers[whichPlayer].rec.height += 45.0f * GetFrameTime();
	}
}