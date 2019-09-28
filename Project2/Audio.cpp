#include "Audio.h"

namespace Ignacio {
	Music gameMusic;

	void initAudio() {
		InitAudioDevice();
		gameMusic = LoadMusicStream("Audio/Megalovania.ogg");
	}

	void closeAudio() {
		UnloadMusicStream(gameMusic);
		CloseAudioDevice();
	}
}