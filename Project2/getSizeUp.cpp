#include "getSizeUp.h"

#include "Players.h"
#include "Barriers.h"

namespace Ignacio {
	void getSizeUp(int whichPlayer) {
		players[whichPlayer].rec.height += 45.0f * GetFrameTime();
		barriers[whichPlayer].rec.height += 45.0f * GetFrameTime();
	}
}