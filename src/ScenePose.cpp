#include "ScenePose.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "MyFileIO.h"
#include "GameMain.h"

int cScenePose::GHandleBk = 0;
int cScenePose::GHandlePose = 0;
int cScenePose::GHandleReturn = 0;
int cScenePose::GHandleTitle = 0;

cScenePose::cScenePose(cSceneGame* parent){

	this->Parent = parent;
	this->SSwitch = this->RETURN;

	auto f = [=](int* gHandle, char* fileTag){
		if(*gHandle == 0){
			*gHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", fileTag).c_str());
		}
	};

	f(&this->GHandleBk, "PoseBackGround");
	f(&this->GHandlePose, "PosePosePic");
	f(&this->GHandleReturn, "PoseReturnPic");
	f(&this->GHandleTitle, "PoseTitlePic");
}

cScenePose::~cScenePose(){

}

void cScenePose::main(){

	auto f = [=](){
		if(this->SSwitch == this->RETURN){
			this->SSwitch = this->TITLE;
		}else{
			this->SSwitch = this->RETURN;
		}
	};

	if(cKeyboard::JustPushKey(KEY_INPUT_RETURN)){
		if(this->SSwitch == this->TITLE){
			this->Parent->SetScene(cSceneGame::SCENE_TITLE);
		}else{
			this->Parent->SetScene(cSceneGame::SCENE_PLAY);
		}
	}else{
		this->Parent->SetScene(cSceneGame::SCENE_STAY);
	}

	if(cKeyboard::JustPushKey(KEY_INPUT_UP)){
		f();
	}

	if(cKeyboard::JustPushKey(KEY_INPUT_DOWN)){
		f();
	}

}

void cScenePose::draw(){

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);

	DrawRectGraph(	0, 0, 0, 0, 800, 600,
					this->GHandleBk , true , false );

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	
	DrawRectGraph(	279, 155, 0, 0, 243, 93,
					this->GHandlePose , true , false );

	if(this->SSwitch == this->TITLE){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}

	DrawRectGraph(	312, 320, 0, 0, 176, 48,
					this->GHandleReturn , true , false );

	if(this->SSwitch == this->RETURN){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
	}else{
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	DrawRectGraph(	337, 380, 0, 0, 127, 48,
					this->GHandleTitle , true , false );

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}