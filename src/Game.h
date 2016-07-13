#ifndef		__GAME_H__
#define		__GAME_H__

#include "GameMain.h"
#include "Scene.h"

class cScenePlay;

class cSceneGame : public cScene{

public:
	typedef enum tag_Scene{
		SCENE_STAY,
		SCENE_POSE,
		SCENE_PLAY,
		SCENE_STAGE_CLEAR,
		SCENE_ALL_CLEAR,
		SCENE_GAMEOVER,
		SCENE_TITLE
	}Scene;
	unsigned StageNo;

private:
	
	cGameMain* Parent;		// �Ăяo�����V�[��
	Scene scene;			// ���݂̃V�[��
	cScenePlay* playObj;	// �v���C�V�[��
	cScene*		sceneObj;	// �v���C�ȊO�̃V�[��

public:

	cSceneGame(cGameMain* parent);
	~cSceneGame();

	void main();
	void draw();

	void SetScene(Scene scene);
	unsigned getScore();
	void nextStage();
	unsigned getStageNo(){ return this->StageNo; }

};

#endif		__GAME_H__