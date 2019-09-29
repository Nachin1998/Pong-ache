#include "Audio.h"

namespace Ignacio {
	Music gameMusic;
	Music endScreenMusic;

	void initAudio() {
		InitAudioDevice();
		SetMasterVolume(masterVolume);
		gameMusic = LoadMusicStream("Music/Megalovania.ogg");
		endScreenMusic = LoadMusicStream("Music/EndScreenSong.ogg");
	}

	void closeAudio() {
		UnloadMusicStream(gameMusic);
		UnloadMusicStream(endScreenMusic);
		CloseAudioDevice();
	}
}