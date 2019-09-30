#include "Audio.h"

namespace IgnacioFernandezLemos {
	Music gameMusic;
	Music endScreenMusic;

	void initAudio() {
		InitAudioDevice();
		SetMasterVolume(masterVolume);
		gameMusic = LoadMusicStream("Music/Megalovania.ogg");
		endScreenMusic = LoadMusicStream("Music/EndScreenSong.wav");
	}

	void closeAudio() {
		UnloadMusicStream(gameMusic);
		UnloadMusicStream(endScreenMusic);
		CloseAudioDevice();
	}
}