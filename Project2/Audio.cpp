#include "Audio.h"

Music gameMusic;

void initAudio() {
	InitAudioDevice();
	gameMusic = LoadMusicStream("Audio/Megalovania.ogg");
}

void closeAudio() {
	UnloadMusicStream(gameMusic);
	CloseAudioDevice();
}