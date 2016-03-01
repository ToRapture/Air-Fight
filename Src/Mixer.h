#ifndef MIXER_H
#define MIXER_H
#define TheMixer Mixer::MixerInstance()

class Mixer {
private:
	static Mixer *pInstance;
	Mix_Chunk *pChunk[3];
	Mix_Music *pMusic;
	Mixer();
public:
	~Mixer();
	static Mixer* MixerInstance() {
		if(pInstance == NULL)
			pInstance = new Mixer;
		return pInstance;
	}
	static void Delete() {
		if(pInstance != NULL) {
			delete pInstance;
			pInstance = NULL;
		}
	}
	void Load();
	void ShutDown();
	void PlaySound(int index);
	void PlayMusic();
};


#endif	//MIXER_H