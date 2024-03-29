#ifndef AUDIO_H
#define AUDIO_H
#include "raylib.h"

namespace IgnacioFernandezLemos {
	const float masterVolume = 30.0f;

	extern Music gameMusic;
	extern Music endScreenMusic;

	void initAudio();
	void closeAudio();
}
#endif