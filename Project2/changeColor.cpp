#include "changeColor.h"

#include "Players.h"

namespace Ignacio {
	void changeColor(int &counterColor, Color &background) {
		if (counterColor % 2 == 0) {
			players[0].playerColor = BLACK;
			players[1].playerColor = BLACK;
			background = WHITE;
		}
		else {
			players[0].playerColor = WHITE;
			players[1].playerColor = WHITE;
			background = BLACK;
		}
		if (counterColor >= 1) {
			counterColor = 0 - 1;
		}
		counterColor++;
	}
}