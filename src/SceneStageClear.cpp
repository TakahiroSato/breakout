#include "WinMain.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "MyFileIO.h"
#include "GameMain.h"
#include "SceneStageClear.h"

int cSceneStageClear::GHandleBk = 0;
int cSceneStageClear::GHandleStageClear = 0;

cSceneStageClear::cSceneStageClear(cSceneGame* parent){

	if(this->GHandleBk == 0){
		this->GHandleBk = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "StageClearBackGround").c_str());
	}
	if(this->GHandleStageClear == 0){
		this->GHandleStageClear = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "StageClearPic").c_str());
	}

	this->parent = parent;
}

cSceneStageClear::~cSceneStageClear(){

}

void cSceneStageClear::main(){
	if(cKeyboard::JustPushKey(KEY_INPUT_RETURN)){
		this->parent->SetScene(this->parent->SCENE_TITLE);
	}
}

void cSceneStageClear::draw(){
	
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawRectGraph(	0, 0, 0, 0, W_WIDTH, W_HEIGHT,
					this->GHandleBk , true , false );

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRectGraph( (800-466)/2, (600-93)/2, 0, 0, 466, 93,
					this->GHandleStageClear, true, false);
}