#ifndef ENEMY_H
#define ENEMY_H
#include <SDL.h>
#include "Slist.h"

#include <stdio.h>
#define Enemys Enemy::EnemyInstance()

class Enemy {
	private:
	static Enemy* pInstance;
	SDL_Rect srcRect;
	SDL_Texture *pTexture;
	Enemy();
	public:
	static Enemy* EnemyInstance() {
		if(pInstance == NULL) {
			pInstance = new Enemy;
		}
		return pInstance;
	}
	static void Delete() {
        if(pInstance != NULL) {
            delete pInstance;
            pInstance = NULL;
        }
	}
	~Enemy();
	struct Info {
		int now,moved,dir;
		Info(int now = 0, int moved = 0, int dir = 0):
		now(now), moved(moved), dir(dir) {}
	};
	Slist<Info> enemys;
	int num;
	void LoadTexture(SDL_Renderer *pRenderer, const char *filename);
	void Draw(SDL_Renderer *pRenderer);
	void Destroy();
	void Create();
	void Fire();
	void Move();
	int GetY() {
		return srcRect.h;
	}
	int GetW() {
		return srcRect.w;
	}
	void Clear();
};


#endif // ENEMY_H
