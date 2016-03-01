#include <SDL.h>
#include "Frame.h"
#include <stdio.h>

int main(int argc, char **argv) {
	int time, newtime, oldtime;
	oldtime = 0;
	TheGame->Init();
	oldtime = SDL_GetTicks();
	
	while(TheGame->Running()) {
		TheGame->Update();
		TheGame->Draw();
		newtime = SDL_GetTicks();
		if(newtime - oldtime < DELAY)
			SDL_Delay(DELAY - (newtime - oldtime));
		oldtime = newtime;
	}
	TheGame->Quit();
	return 0;
}
