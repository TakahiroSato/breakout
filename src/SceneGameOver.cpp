#include "SceneGameOver.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "MyFileIO.h"
#include "GameMain.h"

int cSceneGameOver::GHandleBk = 0;
int cSceneGameOver::GHandleGameOver = 0;
int cSceneGameOver::GHandleTitle = 0;

cSceneGameOver::cSceneGameOver(cSceneGame* parent){

	this->Parent = parent;
	this->SSwitch = this->TITLE;

	auto f = [=](int* gHandle, char* fileTag){
		if(*gHandle == 0){
			*gHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", fileTag).c_str());
		}
	};

	f(&this->GHandleBk, "GameOverBackGround");
	f(&this->GHandleGameOver, "GameOverGameOverPic");
	f(&this->GHandleTitle, "GameOverTitlePic");
}

cSceneGameOver::~cSceneGameOver(){

}

void cSceneGameOver::main(){

	if(cKeyboard::JustPushKey(KEY_INPUT_RETURN)){
		if(this->SSwitch == this->TITLE){
			this->Parent->SetScene(cSceneGame::SCENE_TITLE);
		}
	}else{
		this->Parent->SetScene(cSceneGame::SCENE_STAY);
	}

}

void cSceneGameOver::draw(){

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawRectGraph(	0, 0, 0, 0, 800, 600,
					this->GHandleBk , true , false );

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawRectGraph(	141, 155, 0, 0, 517, 93,
					this->GHandleGameOver , true , false );


	DrawRectGraph(	337, 380, 0, 0, 127, 48,
					this->GHandleTitle , true , false );

}