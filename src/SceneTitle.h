#ifndef		__SCENETITLE_H__
#define		__SCENETITLE_H__

#include "Scene.h"
#include "GameMain.h"

class cSceneTitle : public cScene{

private:
	cGameMain* Parent;
	static int GHandle;
	static int SHandle;
public:
	cSceneTitle(cGameMain* parent);
	~cSceneTitle();

	void main();
	void draw();

};

#endif		__SCENETITLE_H__