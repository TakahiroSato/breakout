#include "SceneTitle.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "MyFileIO.h"
#include "GameMain.h"

int cSceneTitle::GHandle = 0;
int cSceneTitle::SHandle = 0;

cSceneTitle::cSceneTitle(cGameMain* parent){

	this->Parent = parent;		// ƒV[ƒ“ŒÄ‚Ño‚µŒ³“o˜^
	if(this->GHandle == 0){
		this->GHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "TitleBackGround").c_str());
	}

	if(this->SHandle == 0){
		this->SHandle = cGameMain::GetSHandle(cMyFileIO::GetTextInText("config.txt", "TitleSound").c_str());
	}
}

cSceneTitle::~cSceneTitle(){


}

void cSceneTitle::main(){

	if(cKeyboard::JustPushKey(KEY_INPUT_RETURN)){
		this->Parent->SetScene(cGameMain::SCENE_GAME);
		PlaySoundMem(this->SHandle, DX_PLAYTYPE_BACK);
	}else{
		this->Parent->SetScene(cGameMain::SCENE_STAY);
	}
}

void cSceneTitle::draw(){
	DrawRectGraph(0, 0, 0, 0, 800, 600,
					this->GHandle, true , false );
}