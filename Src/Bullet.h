#ifndef BULLET_H
#define BULLET_H

#include "Slist.h"
#include <SDL.h>

#define Bullets Bullet::TheBulletManager()

class Bullet {
	private:
	static Bullet *pInstance;
	SDL_Texture *pTexture;
	SDL_Rect srcRect;
	struct Position{
		int x, y;
		int belong;
		Position(int x = 0,int y = 0,int belong = 0):
		 x(x), y(y), belong(belong) {}
	};
	
	Slist<Position> bullets;
	Bullet();
	public:
	static Bullet* TheBulletManager() {
		if(pInstance == NULL)
			pInstance = new Bullet;
		return pInstance;
	}
	static void Delete() {
        if(pInstance != NULL) {
            delete pInstance;
            pInstance = NULL;
        }
	}
	~Bullet();
	void Create(int x,int y, int belong);
	void LoadTexture(SDL_Renderer *pRenderer, const char *filename);
	void Draw(SDL_Renderer *pRenderer);
	int GetW() {
        return srcRect.w;
	}
	void Update();
	void Destroy();
	void Clear();
};



#endif // BULLET_H
