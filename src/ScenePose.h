#ifndef		__SCENEPOSE_H__
#define		__SCENEPOSE_H__

#include "Scene.h"
#include "Game.h"

class cScenePose : public cScene{

private:
	typedef enum tagSceneSwitch{
		RETURN,
		TITLE
	}SceneSwitch;

	cSceneGame* Parent;
	static int GHandleBk;
	static int GHandlePose;
	static int GHandleReturn;
	static int GHandleTitle;

	SceneSwitch SSwitch;

public:
	cScenePose(cSceneGame* parent);
	~cScenePose();

	void main();
	void draw();

};

#endif		__SCENEPOSE_H__