#ifndef		__GAMEMAIN_H__
#define		__GAMEMAIN_H__

#include "Scene.h"

class cGameMain{

public:
	typedef enum tag_Scene{
		SCENE_STAY,
		SCENE_TITLE,
		SCENE_GAME
	}Scene;

private:
	cScene* sceneObj;
	Scene scene;

public:

	cGameMain();
	~cGameMain();

	void main();

	void SetScene(Scene scene);

	static int GetGHandle(const char *pic_name);
	static int GetSHandle(const char *sound_name);
};

#endif		__GAMEMAIN_H__