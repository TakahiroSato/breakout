#include "GameMain.h"
#include "SceneTitle.h"
#include "Game.h"
#include "DxLib.h"
#include "WinMain.h"

cGameMain::cGameMain(){
	this->scene = SCENE_STAY;

	// タイトルシーン作成
	this->sceneObj = new cSceneTitle(this);

	// 透過色(R,G,B)を(255,0,255)に設定
	//SetTransColor(255,0,255);
}

cGameMain::~cGameMain(){
	
	// 作ったシーンを破棄
	SAFE_DELETE(this->sceneObj);

}

void cGameMain::main(){

	// シーン分け処理
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

// シーン設定用関数
void cGameMain::SetScene(Scene scene){

	this->scene = scene;

}

int cGameMain::GetGHandle(const char* pic_name){
	int GHandle = LoadGraph(pic_name);
	if( GHandle == -1 ) printf("LoadGraphエラー\n");

	return GHandle;
}

int cGameMain::GetSHandle(const char* sound_name){
	int SHandle = LoadSoundMem(sound_name);
	if(SHandle == -1){
		printf("LoadSoundMemエラー\n");
		return -1;
	}

	ChangeVolumeSoundMem(5, SHandle) ;

	return SHandle;
}
