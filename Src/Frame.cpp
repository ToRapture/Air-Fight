#include "Frame.h"
#include "Bullet.h"
#include "Enemy.h"
#include "common.h"
#include "Mixer.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <string.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

GameFrame* GameFrame::pInstance = NULL;

GameFrame::GameFrame() {	//成员变量初始化
	pWindow = NULL;
	pRenderer = NULL;
	pFont = NULL;
	for(int i = DIE; i < EXIT_TYPE_TOTAL; ++i) {
		pTexture[i] = NULL;
	}
	backgroundID = 0;
	running = true;
}
GameFrame::~GameFrame() {

}

void GameFrame::LoadExitTexture() {
	SDL_Surface *tempSurface = NULL;
	for(int i = DIE; i < EXIT_TYPE_TOTAL; ++i) {
		char filename[128] = FILE_PATH;
		if(i == DIE)
			strcat(filename,GAMEOVER_FILE);
		else if(i == EXIT)
			strcat(filename,BYE_FILE);
		tempSurface = IMG_Load(filename);
		pTexture[i] = SDL_CreateTextureFromSurface(pRenderer,tempSurface);
		SDL_FreeSurface(tempSurface);
	}
}


void GameFrame::Init() {
	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	Mix_Init(MIX_INIT_MP3);
	Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 );
	srand(time(NULL));
	pWindow = SDL_CreateWindow(APP_NAME, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
	                           SCREEN_W,SCREEN_H, SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
	pRenderer = SDL_CreateRenderer(pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/**
	  use consola.ttf in windows
	  use Ubuntu-M.ttf in Ubuntu
	*/
	pFont = TTF_OpenFont("../Res/consolab.ttf", 15);
	
	this->LoadExitTexture();
	TheMixer->Load();

	SDL_Surface *tempSurface;
	char file[32] = "../Res/1.jpg";
	for(int i = 0; i < 4; ++i) {
		file[7] = i + '1';
		tempSurface = IMG_Load(file);
		pBackGround[i] = SDL_CreateTextureFromSurface(pRenderer,tempSurface);
		SDL_FreeSurface(tempSurface);
	}

	ThePlayer->LoadTexture(pRenderer,PLAYER_FILE);
	Enemys->LoadTexture(pRenderer,ENEMY_FILE);
	Bullets->LoadTexture(pRenderer,BULLET_FILE);

}

void GameFrame::DrawTexture(int drawID) {
	if(Mix_PlayingMusic() == 1) {
		Mix_PauseMusic();
	}
	if(drawID == DIE)
		TheMixer->PlaySound(LAUGH);
	if(drawID == EXIT) {
		SDL_RenderClear(pRenderer);
		SDL_RenderCopy(pRenderer, pTexture[drawID],NULL,NULL);
		SDL_RenderPresent(pRenderer);
		SDL_Delay(GAMEOVER_DELAY_TIME);
	} else {
		DrawScore();
	}
}

void GameFrame::DrawScore() {
	SDL_Color color = { 0xFF, 0xFF, 0xFF };
	SDL_Rect strRect = { SCREEN_W / 5, SCREEN_H / 6, SCREEN_W * 3 / 5, SCREEN_H * 2 / 5 };
	SDL_Rect scoreRect = { SCREEN_W * 3 / 8, SCREEN_H * 3 / 6, SCREEN_W / 4, SCREEN_H * 2 / 5 };
	char scoreStr[128];
	sprintf(scoreStr, "%d", ThePlayer->GetScore());
	SDL_RenderClear(pRenderer);
	SDL_Surface *tempSurface = TTF_RenderText_Solid(pFont, "Score", color);
	SDL_Texture *tempTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);

	SDL_RenderSetViewport(pRenderer, &strRect);
	SDL_RenderCopy(pRenderer,tempTexture,NULL,NULL);
	SDL_DestroyTexture(tempTexture);
	SDL_FreeSurface(tempSurface);

	tempSurface = TTF_RenderText_Solid(pFont, scoreStr, color);
	tempTexture = SDL_CreateTextureFromSurface(pRenderer,tempSurface);
	SDL_RenderSetViewport( pRenderer, &scoreRect );
	SDL_RenderCopy(pRenderer,tempTexture,NULL,NULL);
	SDL_DestroyTexture(tempTexture);
	SDL_FreeSurface(tempSurface);

	SDL_RenderPresent(pRenderer);
	SDL_RenderSetViewport( pRenderer, NULL);
	SDL_Delay(GAMEOVER_DELAY_TIME);
}

void GameFrame::DestroyExitTexture() {
	for(int i = DIE; i < EXIT_TYPE_TOTAL; ++i) {
		SDL_DestroyTexture(pTexture[i]);
	}
}

void GameFrame::Quit() {

	ThePlayer->Destroy();
	ThePlayer->Delete();

	Enemys->Destroy();
	Enemys->Delete();

	Bullets->Destroy();
	Bullets->Delete();

	this->DestroyExitTexture();

	for(int i = 0; i < 4; ++i)
		SDL_DestroyTexture(pBackGround[i]);
	
	TTF_CloseFont(pFont);
	SDL_DestroyRenderer(pRenderer);
	SDL_DestroyWindow(pWindow);
	TheMixer->ShutDown();
	this->Delete();

	IMG_Quit();
	Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}

void GameFrame::Draw() {

	SDL_RenderClear(pRenderer);
	SDL_RenderCopy(pRenderer, pBackGround[backgroundID], NULL, NULL);
	ThePlayer->Draw(pRenderer);
	Enemys->Draw(pRenderer);
	Bullets->Draw(pRenderer);
	SDL_RenderPresent(pRenderer);

}

void GameFrame::UpdateBackground() {
	this->backgroundID = (this->backgroundID + 1) % 4;
}

void GameFrame::Update() {
	SDL_Event Event;
	static bool moveLeft = false, moveRight = false, onfire = false;
	TheMixer->PlayMusic();
	while(SDL_PollEvent(&Event)) {
		if(Event.type == SDL_QUIT) {
			running = false;
			this->DrawTexture(EXIT);
			Mix_HaltMusic();
			break;
		} else if(Event.type == SDL_KEYDOWN) {
			if(Event.key.keysym.sym == SDLK_LEFT) {
				moveLeft = true;
			}
			if(Event.key.keysym.sym == SDLK_RIGHT) {
				moveRight = true;
			}
			if(Event.key.keysym.sym == SDLK_SPACE) {
				onfire = true;
			}	
		} else if(Event.type == SDL_KEYUP) {
			if(Event.key.keysym.sym == SDLK_SPACE) {
				onfire = false;
			} else if(Event.key.keysym.sym == SDLK_LEFT) {
				moveLeft = false;
			} else if(Event.key.keysym.sym == SDLK_RIGHT) {
				moveRight = false;
			}
		}
	}
	if(moveLeft ^ moveRight) {
		if(moveLeft) ThePlayer->Move(LEFT);
		if(moveRight) ThePlayer->Move(RIGHT);
	}
	if(onfire) {
		ThePlayer->Fire();
		TheMixer->PlaySound(FIRE);
	}
	Enemys->Create();
	Enemys->Fire();
	Bullets->Update();
	Enemys->Move();
	if(ThePlayer->IsDie()) {
		this->DrawTexture(DIE);
		this->UpdateBackground();
		ThePlayer->Respawn();
		Enemys->Clear();
		Bullets->Clear();
	}
}
