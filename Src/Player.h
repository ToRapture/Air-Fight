#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include "common.h"
#define ThePlayer  Player::PlayerInstance()

class Player {
	private:
	SDL_Rect srcRect, destRect;
	SDL_Texture *pTexture;
	bool die;
	int pos_x;
	int score;
	Player();
	static Player* pInstance;
	public:
	static Player* PlayerInstance() {
		if(pInstance == NULL) {
			pInstance = new Player;
		}
		return pInstance;
	}
	static void Delete() {
        if(pInstance != NULL) {
            delete pInstance;
            pInstance = NULL;
        }

	}
	~Player();
	void Draw(SDL_Renderer *pRenderer);
	void LoadTexture(SDL_Renderer *renderer, const char *filename);
	void Destroy();
	void Move(int dir);
	void Fire();
	bool IsDie() {
		return die;
	}
	void Die() {
		die = true;
	}
	void Respawn() {
        die = false;
        score = 0;
	}
	int GetX() {
		return pos_x;
	}
	int GetY() {
		return SCREEN_H - srcRect.h;
	}
	int GetW() {
		return srcRect.w;
	}
	int GetScore() {
        return score;
	}
	void ScoreUp() {
        score += SCORE_PER_KILL;
	}
};

#endif // PLAYER_H
