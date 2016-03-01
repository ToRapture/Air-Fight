#include "Bullet.h"
#include "common.h"
#include "Player.h"
#include "Frame.h"
#include "Mixer.h"
#include <string.h>
#include <SDL_image.h>
#include "Enemy.h"
#include <math.h>
Bullet* Bullet::pInstance = NULL;

Bullet::Bullet() {}
Bullet::~Bullet() {

}

void Bullet::Destroy() {

	while(bullets.head != NULL) {
		Slist<Position>::Element *next = bullets.head->next;
		delete bullets.head;
		bullets.head = next;

	}
	if(pTexture != NULL) {
		SDL_DestroyTexture(pTexture);
		pTexture = NULL;
	}
}

void Bullet::Clear() {
	Slist<Position>::Element *head = bullets.head->next;
	Slist<Position>::Element *pre = bullets.head;
	while(head != NULL)
		head = bullets.Delete(head,pre);
}

void Bullet::LoadTexture(SDL_Renderer *pRenderer, const char *filename) {
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

void Bullet::Create(int x,int y,int belong) {
	if(belong == ENEMY)
		y -= srcRect.h;
	bullets.PushBack(Position(x,y,belong));
}

void Bullet::Draw(SDL_Renderer *pRenderer) {
	SDL_Rect destRect = srcRect;
	Slist<Position>::Element* head = bullets.head->next;
	SDL_RendererFlip flag;
	while(head != NULL) {
		destRect.x = head->data.x - srcRect.w / 2;
		destRect.y = head->data.y;
		flag = head->data.belong == PLAYER ? SDL_FLIP_NONE : SDL_FLIP_VERTICAL;
		head = head->next;
		SDL_RenderCopyEx(pRenderer,pTexture,&srcRect,&destRect,0.00,NULL,flag);

	}
}

void Bullet::Update() {
	Slist<Position>::Element* head = bullets.head->next;
	Slist<Position>::Element* pre  = bullets.head;

	while(head != NULL) {
		if(head->data.belong == PLAYER) {
			head->data.y -= BULLET_MOVE_SPEED;
			if(head->data.y >= 0 && head->data.y <= Enemys->GetY()) {
				Slist<Enemy::Info>::Element *thead = Enemys->enemys.head->next;
				Slist<Enemy::Info>::Element *tpre = Enemys->enemys.head;
				while(thead != NULL) {
					if(abs(thead->data.now - head->data.x) <= (Enemys->GetW() + GetW()) / 2) {
						thead = Enemys->enemys.Delete(thead,tpre);
						--Enemys->num;
						ThePlayer->ScoreUp();
						TheMixer->PlaySound(BOOM);		//go
					} else {
						tpre = tpre->next;
						thead = thead->next;
					}
				}
			}
			if(head->data.y + srcRect.h < 0) {
				head = bullets.Delete(head,pre);
			} else {
				pre = pre->next;
				head = head->next;
			}
		} else {
			head->data.y += BULLET_MOVE_SPEED;
			if(head->data.y >= ThePlayer->GetY() && head->data.y <= SCREEN_H) {
				if(abs(head->data.x - ThePlayer->GetX()) <= (ThePlayer->GetW() + GetW()) / 2) {
					TheMixer->PlaySound(BOOM);
					ThePlayer->Die();
				}
			}
			if(head->data.y - srcRect.h > SCREEN_H) {
				head = bullets.Delete(head,pre);
			} else {
				pre = pre->next;
				head = head->next;
			}
		}
	}
}

