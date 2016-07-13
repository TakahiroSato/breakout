#include "GameMain.h"
#include "SceneTitle.h"
#include "Game.h"
#include "DxLib.h"
#include "WinMain.h"

cGameMain::cGameMain(){
	this->scene = SCENE_STAY;

	// �^�C�g���V�[���쐬
	this->sceneObj = new cSceneTitle(this);

	// ���ߐF(R,G,B)��(255,0,255)�ɐݒ�
	//SetTransColor(255,0,255);
}

cGameMain::~cGameMain(){
	
	// ������V�[����j��
	SAFE_DELETE(this->sceneObj);

}

void cGameMain::main(){

	// �V�[����������
	switch(this->scene){
		case SCENE_STAY:
			break;
		case SCENE_TITLE:
			SAFE_DELETE(this->sceneObj);
			this->sceneObj = new cSceneTitle(this);
			this->scene = SCENE_STAY;
			break;
		case SCENE_GAME:
			SAFE_DELETE(this->sceneObj);
			this->sceneObj = new cSceneGame(this);
			this->scene = SCENE_STAY;
			break;
	}

	this->sceneObj->main();

	this->sceneObj->draw();

}

// �V�[���ݒ�p�֐�
void cGameMain::SetScene(Scene scene){

	this->scene = scene;

}

int cGameMain::GetGHandle(const char* pic_name){
	int GHandle = LoadGraph(pic_name);
	if( GHandle == -1 ) printf("LoadGraph�G���[\n");

	return GHandle;
}

int cGameMain::GetSHandle(const char* sound_name){
	int SHandle = LoadSoundMem(sound_name);
	if(SHandle == -1){
		printf("LoadSoundMem�G���[\n");
		return -1;
	}

	ChangeVolumeSoundMem(5, SHandle) ;

	return SHandle;
}
