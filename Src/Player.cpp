#include "Player.h"
#include "Bullet.h"
#include "common.h"

#include <SDL_image.h>
#include <string.h>
#include <stdio.h>


Player* Player::pInstance = NULL;

Player::Player() {
	pTexture = NULL;
	die = false;
	score = 0;
}
Player::~Player() {

}

void Player::Draw(SDL_Renderer *pRenderer) {
	destRect.x = pos_x - srcRect.w / 2;
	SDL_RenderCopy(pRenderer, pTexture, &srcRect, &destRect);
}

void Player::LoadTexture(SDL_Renderer *pRenderer, const char *filename) {
	char file[128] = FILE_PATH;
	SDL_Surface *tempSurface = NULL;

	strcat(file,filename);
	tempSurface = IMG_Load(file);
	SDL_SetColorKey(tempSurface,SDL_TRUE,SDL_MapRGB(tempSurface->format, 0x0, 0x0, 0x0));
	pTexture = SDL_CreateTextureFromSurface(pRenderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	SDL_QueryTexture(pTexture, NULL, NULL, &srcRect.w, &srcRect.h);

	srcRect.x = srcRect.y = 0;
	destRect.w = srcRect.w;
	destRect.h = srcRect.h;
	pos_x = SCREEN_W / 2;
	destRect.y = SCREEN_H - srcRect.h;
}


void Player::Destroy() {
	if(pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
	}
}

void Player::Move(int dir) {
	if(LEFT == dir) {
		pos_x -= PLAYER_MOVE_SPEED;
	}
	else if(RIGHT == dir) {
		pos_x += PLAYER_MOVE_SPEED;
	}
	if(pos_x < srcRect.w / 2) {
		pos_x = srcRect.w / 2;
	}
	if(pos_x + srcRect.w / 2 > SCREEN_W) {
		pos_x = SCREEN_W - srcRect.w / 2;
	}
}

void Player::Fire() {
	static int oldtime = SDL_GetTicks();
	static int newtime = SDL_GetTicks();
	newtime = SDL_GetTicks();
	if(newtime - oldtime < PLAYER_FIRE_TIME) return;
	oldtime = SDL_GetTicks();
	Bullets->Create(pos_x, SCREEN_H - srcRect.h, PLAYER);
}
