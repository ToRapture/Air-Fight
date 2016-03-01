#include "Enemy.h"
#include "Bullet.h"
#include "common.h"
#include "Frame.h"
#include "Mixer.h"
#include <string.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_image.h>
Enemy* Enemy::pInstance = NULL;

Enemy::Enemy() {
    num = 0;
    pTexture = NULL;
}

Enemy::~Enemy() {

}

void Enemy::LoadTexture(SDL_Renderer *pRenderer, const char *filename) {
    char file[128] = FILE_PATH;
    SDL_Surface *tempSurface = NULL;

    strcat(file,filename);
    tempSurface = IMG_Load(file);
	SDL_SetColorKey(tempSurface,SDL_TRUE,SDL_MapRGB(tempSurface->format,0x0,0x0,0x0));
    pTexture = SDL_CreateTextureFromSurface(pRenderer,tempSurface);
    SDL_FreeSurface(tempSurface);

    SDL_QueryTexture(pTexture,NULL,NULL,&srcRect.w, &srcRect.h);
    srcRect.x = srcRect.y = 0;
}

void Enemy::Draw(SDL_Renderer *pRenderer) {
    SDL_Rect destRect = srcRect;
    Slist<Info>::Element* head = enemys.head->next;
    while(head != NULL) {
        destRect.x = head->data.now - srcRect.w / 2;
        destRect.y = 0;
        head = head->next;
        SDL_RenderCopy(pRenderer,pTexture,&srcRect,&destRect);
    }
}

void Enemy::Create() {
    static int oldtime = SDL_GetTicks();
    static int newtime, time;
    newtime = SDL_GetTicks();
    time = newtime - oldtime;
    if(time > ENEMY_CREATE_TIME && num < ENEMY_NUM_MAX) {
        int pos = rand() % SCREEN_W;
        enemys.PushBack(Info(pos,0,rand() % 2));
        ++num;
        oldtime = newtime;
    }
}
void Enemy::Fire() {
    static int newtime,time;
    static int oldtime = SDL_GetTicks();
    newtime = SDL_GetTicks();
    time = newtime - oldtime;
    if(time >= ENEMY_FIRE_TIME) {
        Slist<Info>::Element* head = enemys.head->next;
        while(head != NULL) {
            if(rand() % 2) {
                Bullets->Create(head->data.now, Enemys->GetY(), ENEMY);
                TheMixer->PlaySound(FIRE);		//go
            }
            head = head->next;
        }
        oldtime = newtime;
    }



}
void Enemy::Move() {
    Slist<Info>::Element* head = enemys.head->next;
    while(head != NULL) {
        if(head->data.now <= 0) {
            head->data.now = 0;
            head->data.moved = 0;
            head->data.dir = RIGHT;
        } else if(head->data.now + srcRect.w >= SCREEN_W) {
            head->data.now = SCREEN_W - srcRect.w;
            head->data.moved = 0;
            head->data.dir = LEFT;
        }
        if(head->data.moved >= ENEMY_MOVE_LEN) {
            head->data.moved = 0;
            head->data.dir = !head->data.dir;
        }
        if(head->data.dir == LEFT) {
            head->data.now -= ENEMY_MOVE_SPEED;
            head->data.moved += ENEMY_MOVE_SPEED;
        } else {
            head->data.now += ENEMY_MOVE_SPEED;
            head->data.moved +=  ENEMY_MOVE_SPEED;
        }
        head = head->next;
    }
}
void Enemy::Destroy() {     //Todo
	while(enemys.head != NULL) {
		Slist<Info>::Element *next = enemys.head->next;
		delete enemys.head;
		enemys.head = next;
	}

	if(pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
	}
}

void Enemy::Clear() {
    Slist<Info>::Element *head = enemys.head->next;
    Slist<Info>::Element *pre = enemys.head;
    while(head != NULL) {
        head = Enemys->enemys.Delete(head,pre);
        --Enemys->num;
    }
}
