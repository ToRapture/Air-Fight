#ifndef FRAME_H
#define FRAME_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "common.h"
#include "Player.h"
#define TheGame GameFrame::FrameInstance()

class GameFrame{
	private:
	static GameFrame *pInstance;
	int backgroundID;
	SDL_Window *pWindow;
	SDL_Renderer *pRenderer;
	SDL_Texture *pTexture[EXIT_TYPE_TOTAL];
	SDL_Texture *pBackGround[4];
	TTF_Font *pFont;
	bool running;
	GameFrame();
	public:
	static GameFrame* FrameInstance() {
		if(pInstance == NULL)
			pInstance = new GameFrame;
		return pInstance;
	}
	static void Delete() {
        if(pInstance != NULL) {
            delete pInstance;
            pInstance = NULL;
        }
	}
	~GameFrame();
	void Init();
	void Quit();
	void Update();
	void Draw();
	bool Running() {
		return running;
	}
	void LoadExitTexture();
	void DrawTexture(int drawID);
	void DestroyExitTexture();
	void DrawScore();
	void UpdateBackground();
};


#endif //FRAME_H
