#ifndef		__SCENEGAMEOVER_H__
#define		__SCENEGAMEOVER_H__

#include "Scene.h"
#include "Game.h"

class cSceneGameOver : public cScene{

private:
	typedef enum tagSceneSwitch{
		TITLE
	}SceneSwitch;

	cSceneGame* Parent;
	static int GHandleBk;
	static int GHandleGameOver;
	static int GHandleTitle;

	SceneSwitch SSwitch;

public:
	cSceneGameOver(cSceneGame* parent);
	~cSceneGameOver();

	void main();
	void draw();

};

#endif		__SCENEGAMEOVER_H__