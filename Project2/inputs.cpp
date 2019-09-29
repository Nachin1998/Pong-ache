#include "inputs.h"

#include "variables.h"

#include "Players.h"


namespace Ignacio {
	void inputs() {
		if (IsKeyDown(KEY_W)) players[0].rec.y -= movementSpeed * GetFrameTime();
		if (IsKeyDown(KEY_S)) players[0].rec.y += movementSpeed * GetFrameTime();

		if (IsKeyDown(KEY_UP)) players[1].rec.y -= movementSpeed * GetFrameTime();
		if (IsKeyDown(KEY_DOWN)) players[1].rec.y += movementSpeed * GetFrameTime();
	}
}