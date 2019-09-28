#ifndef BARRIERS_H
#define BARRIERS_H
#include "raylib.h"

namespace Ignacio {
	const int barrierMax = 2;

	struct Barrier {
		Rectangle rec;
		Vector2 size;
		Color playerColor;
		bool active;
	};

	extern Barrier barriers[barrierMax];
	void setBarrierParameters();
	void barrierShooting();
}

#endif