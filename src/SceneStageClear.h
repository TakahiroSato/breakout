#ifndef		__SCENESTAGECLEAR_H__
#define		__SCENESTAGECLEAR_H__

#include "Scene.h"
#include "Game.h"

class cSceneStageClear : public cScene{

private:
	cSceneGame* parent;
	static int GHandleBk;
	static int GHandleStageClear;

public:
	cSceneStageClear(cSceneGame* parent);
	~cSceneStageClear();

	void main();
	void draw();
};

#endif		__SCENESTAGECLEAR_H__