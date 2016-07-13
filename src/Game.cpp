#include "WinMain.h"
#include "Game.h"
#include "ScenePlay.h"
#include "ScenePose.h"
#include "SceneStageClear.h"
#include "SceneGameOver.h"
#include "MyFileIO.h"
#include <string.h>

// コンストラクタ
cSceneGame::cSceneGame(cGameMain* parent){

	this->Parent = parent;	// シーン呼び出し元登録

	this->scene = SCENE_PLAY;

	this->playObj = new cScenePlay(this);
	this->sceneObj = NULL;

	this->StageNo = 0;
}

// デストラクタ
cSceneGame::~cSceneGame(){
	
	SAFE_DELETE(this->playObj);
	SAFE_DELETE(this->sceneObj);

}

// メイン処理
void cSceneGame::main(){

	if(this->scene == SCENE_PLAY){
		this->playObj->StopWatchUpdate(0);
	}else{
		this->playObj->StopWatchUpdate(1);
	}

	switch(this->scene){
		case SCENE_STAY:
			break;
		case SCENE_PLAY:
			SAFE_DELETE(this->sceneObj);
			this->playObj->main();
			break;
		case SCENE_POSE:
			SAFE_DELETE(this->sceneObj);
			this->sceneObj = new cScenePose(this);
			this->scene = SCENE_STAY;
			break;
		case SCENE_STAGE_CLEAR:
			SAFE_DELETE(this->sceneObj);
			this->sceneObj = new cSceneStageClear(this);
			this->scene = SCENE_STAY;
			break;
		case SCENE_ALL_CLEAR:
			SAFE_DELETE(this->sceneObj);
			this->scene = SCENE_STAY;
			break;
		case SCENE_GAMEOVER:
			SAFE_DELETE(this->sceneObj);
			this->sceneObj = new cSceneGameOver(this);
			this->scene = SCENE_STAY;
			break;
		case SCENE_TITLE:
			SAFE_DELETE(this->sceneObj);
			this->Parent->SetScene(cGameMain::SCENE_TITLE);
			this->scene = SCENE_STAY;
			break;
	}

	if(this->sceneObj != NULL){
		this->sceneObj->main();
	}

}

// 描画処理
void cSceneGame::draw(){

	this->playObj->draw();

	if(this->sceneObj != NULL){
		this->sceneObj->draw();
	}

}

// シーン設定用関数
void cSceneGame::SetScene(Scene scene){

	this->scene = scene;

}

unsigned cSceneGame::getScore(){
	return this->playObj->getScore();
}

void cSceneGame::nextStage(){
	std::string mapName;

	this->StageNo++;

	switch(this->StageNo){
		case 0:
			mapName = cMyFileIO::GetTextInText("config.txt", "StageZero");
			break;
		case 1:
			mapName = cMyFileIO::GetTextInText("config.txt", "StageOne");
			break;
		case 2:
			mapName = cMyFileIO::GetTextInText("config.txt", "StageTwo");
			break;
		case 3:
			mapName = cMyFileIO::GetTextInText("config.txt", "StageThree");
			break;
		case 4:
			this->SetScene(this->SCENE_TITLE);
			return;
		default:
			return;
	}
	
	this->playObj->ChangeStage(mapName.c_str());
}