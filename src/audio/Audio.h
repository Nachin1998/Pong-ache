#ifndef AUDIO_H
#define AUDIO_H
#include "raylib.h"

namespace IgnacioFernandezLemos {
	const float masterVolume = 30.0f;

	extern Music gameMusic;
	extern Music endScreenMusic; //Wont load, maybe the file is too short?

	void initAudio();
	void closeAudio();
}
#endif