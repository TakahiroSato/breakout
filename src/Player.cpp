#include "Player.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "GameMain.h"
#include "MyFileIO.h"
#include "ScenePlay.h"

const int speed = 10;
int cPlayer::GHandle = 0;

cPlayer::cPlayer(cScenePlay* parent){

	this->Parent = parent;
	
	if(this->GHandle == 0){
		this->GHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "BarPic").c_str());
	}
	this->X = 420;
	this->Y = 500;
	this->Width = cMyFileIO::GetIntInText("config.txt", "BarWidth");
	this->origWidth = this->Width;
	this->additionalWidth = 0;
	this->Height = cMyFileIO::GetIntInText("config.txt", "BarHeight");
	this->PicWidth = cMyFileIO::GetIntInText("config.txt", "BarPicWidth");
	this->PicHeight = cMyFileIO::GetIntInText("config.txt", "BarPicHeight");
	this->PicSrcX = cMyFileIO::GetIntInText("config.txt", "BarPicX");
	this->PicSrcY = cMyFileIO::GetIntInText("config.txt", "BarPicY");
	this->VX = speed;
	this->VY = 0;

}

cPlayer::~cPlayer(){}

void cPlayer::main(){

	// バーの幅決定
	this->Width = this->origWidth + static_cast<int>(this->additionalWidth);

	if(this->additionalWidth > 0){
		this->additionalWidth -= 0.1;
		this->X += 0.05;
	}else{
		this->additionalWidth = 0;
	}

	this->X += this->VX;
	this->Y += this->VY;
	
	if(this->X < 200){
		this->X = 200;
	}else if(this->X+this->Width > 775){
		this->X = 775-this->Width;
	}

	this->VX = 0;
	this->VY = 0;

	if( cKeyboard::JustPushKey(KEY_INPUT_RIGHT) ){
		this->VX = speed;
	}
	if( cKeyboard::JustPushKey(KEY_INPUT_LEFT) ){
		this->VX = -speed;
	}

	if( cKeyboard::KeepPushKey(KEY_INPUT_RIGHT) ){
		this->VX = speed;
	}
	if( cKeyboard::KeepPushKey(KEY_INPUT_LEFT) ){
		this->VX = -speed;
	}

/*	if(cKeyboard::JustPushKey(KEY_INPUT_SPACE)){
		this->Parent->LaunchPlayerBall();
	}*/

}

void cPlayer::draw(){

	int i = 0;

	// 左端
	DrawRectGraph(	static_cast<int>(this->X) , 
					static_cast<int>(this->Y),
					this->PicSrcX , this->PicSrcY , this->PicHeight , this->PicHeight ,
					this->GHandle , true , false );

	DrawRectGraph(	static_cast<int>(this->X) + this->PicHeight , 
					static_cast<int>(this->Y),
					this->PicSrcX + this->PicHeight , this->PicSrcY , this->PicWidth - this->PicHeight*2, this->PicHeight ,
					this->GHandle , true , false );

	// 追加分描画
	for(i = 0 ; i < this->additionalWidth ; i++){
		DrawRectGraph(	static_cast<int>(this->X) + this->PicWidth - this->PicHeight + i, 
						static_cast<int>(this->Y),
						this->PicSrcX + this->PicHeight , this->PicSrcY , 1, this->PicHeight ,
						this->GHandle , true , false );
	}

	// 右端描画
	DrawRectGraph(	static_cast<int>(this->X) + this->PicWidth - this->PicHeight + static_cast<int>(this->additionalWidth), 
					static_cast<int>(this->Y),
					this->PicSrcX + this->PicWidth - this->PicHeight, this->PicSrcY , this->PicHeight , this->PicHeight ,
					this->GHandle , true , false );
}

void cPlayer::hitLR(cCharacter* ch, int chNum){
	
}

void cPlayer::hitTB(cCharacter* ch, int chNum){
	
}

void cPlayer::addWidth(int addWidth){
	this->additionalWidth += addWidth;
	this->X -= addWidth/2;
}