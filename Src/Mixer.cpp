#include <SDL.h>
#include <SDL_mixer.h>
#include "Mixer.h"

Mixer* Mixer::pInstance = NULL;

Mixer::Mixer() {
	for(int i = 0; i < 3; ++i)
		pChunk[i] = NULL;
	pMusic = NULL;
}

Mixer::~Mixer() {

}

void Mixer::Load() {
	pChunk[0] = Mix_LoadWAV("../Res/bullet.wav");
	pChunk[1] = Mix_LoadWAV("../Res/enemy_down.wav");
	pChunk[2] = Mix_LoadWAV("../Res/game_over.wav");
	pMusic = Mix_LoadMUS("../Res/game_music.mp3");
}

void Mixer::ShutDown() {
	for(int i = 0; i < 3; ++i)
		Mix_FreeChunk(pChunk[i]);
	Mix_FreeMusic(pMusic);
}

void Mixer::PlaySound(int index) {
	Mix_PlayChannel(-1, pChunk[index], 0);
}

void Mixer::PlayMusic() {
	if(Mix_PlayingMusic() == 0)	//mixer->Play()
		Mix_PlayMusic(pMusic, -1);
	else if(Mix_PausedMusic() == 1)
		Mix_ResumeMusic();
}