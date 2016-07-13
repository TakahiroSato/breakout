#include "DxLib.h"
#include "Ball.h"
#include "GameMain.h"
#include "MyFileIO.h"
#include "WinMain.h"
#include <math.h>
#include <stdio.h>

int cBall::GHandle = 0;
int cBall::SHandleHit = 0;

cBall::cBall(double dstX, double dstY, double vx, double vy, cBallMgr* parent){

	this->Parent = parent;

	if(this->GHandle == 0){
		this->GHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "BallPic").c_str());
	}

	if(this->SHandleHit == 0){
		this->SHandleHit = cGameMain::GetSHandle(cMyFileIO::GetTextInText("config.txt", "BallSoundHit").c_str());
	}

	this->X = dstX;
	this->Y = dstY;
	this->VX = vx;
	this->VY = vy;

	auto set = [=](int* num, char* Name){
		*num = cMyFileIO::GetIntInText("config.txt", Name);
	};

	set(&this->Width, "BallWidth");
	set(&this->Height, "BallHeight");
	set(&this->PicWidth, "BallPicWidth");
	set(&this->PicHeight, "BallPicHeight");
	set(&this->PicSrcX, "BallPicX");
	set(&this->PicSrcY, "BallPicY");

	this->LR = KEEP;
	this->UD = KEEP;
}

cBall::~cBall(){

}

void cBall::main(){

	this->MoveSet();

	this->X += this->VX;
	this->Y += this->VY;

	if(this->X <= 200){
		this->X = 200;
		this->MoveDirection(RIGHT, KEEP);
		PlaySoundMem(this->SHandleHit, DX_PLAYTYPE_BACK);
	}else if(this->X+this->Width >= 775){
		this->X = 775-this->Width;
		this->MoveDirection(LEFT, KEEP);
		PlaySoundMem(this->SHandleHit, DX_PLAYTYPE_BACK);
	}

	if(this->Y <= 25){
		this->Y = 25;
		this->MoveDirection(KEEP, DOWN);
		PlaySoundMem(this->SHandleHit, DX_PLAYTYPE_BACK);
	}else if(this->Y >= 600){
		this->flag = false;
	}

}

void cBall::draw(){

	if(this->Parent->getPowerFlag() > 0){
		int width = 0;
		if(this->Parent->getPowerFlag() % 8 < 4){
			width = this->PicWidth;
		}

		DrawRectGraph(	static_cast<int>(this->X) , 
						static_cast<int>(this->Y) , 
						this->PicSrcX + width , this->PicSrcY , this->PicWidth , this->PicHeight ,
						this->GHandle , true , false );
	}else{
		DrawRectGraph(	static_cast<int>(this->X) , 
						static_cast<int>(this->Y) , 
						this->PicSrcX, this->PicSrcY , this->PicWidth , this->PicHeight ,
						this->GHandle , true , false );
	}
}

void cBall::hitLR(cCharacter* ch, int chNum){

	PlaySoundMem(this->SHandleHit, DX_PLAYTYPE_BACK);

	switch(chNum){
	case cScenePlay::CH_BLOCK:
		break;
	case cScenePlay::CH_PLAYER:
		if(this->X < ch->X){
			this->MoveDirection(this->LEFT, this->UP);
		}else{
			this->MoveDirection(this->RIGHT, this->UP);
		}
		//this->X += ch->VX;
		this->Y = ch->Y - this->Height-1;
		break;
	default:
		this->VX *= -1;
		this->VY *= -1;
		break;
	}

}

void cBall::hitTB(cCharacter* ch, int chNum){
	
	PlaySoundMem(this->SHandleHit, DX_PLAYTYPE_BACK);

	double rad = 0;
	
	switch(chNum){
	case cScenePlay::CH_BLOCK:
		break;
	case cScenePlay::CH_PLAYER:
		if(this->VY > 0){
			rad = (80+(rand() % 20))*(M_PI/180);
		}else{
			rad = (260+(rand() % 20))*(M_PI/180);
		}
		if(this->X < ch->X+ch->Width/3){
			rad += 45*(M_PI/180);
		}else if(this->X+this->Width > ch->X+ch->Width-ch->Width/3){
			rad -= 45*(M_PI/180);
		}
		this->VX = cos(rad)*cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
		this->VY = -sin(rad)*cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
		break;
	default:
		VY *= -1;
		break;
	}
}

/*
	lr ; true = 右に行け false = 左に行け
	ud ; true = 上に行け false = 下に行け
*/
void cBall::MoveDirection(Direction lr, Direction ud){

	this->LR = lr;
	this->UD = ud;

}

void cBall::MoveSet(){

	double rad = 0;

	switch(this->LR){
		case RIGHT:
			if(this->VX < 0) this->VX *= -1;
			break;
		case LEFT:
			if(this->VX > 0) this->VX *= -1;
			break;
		case KEEP:
			break;
	}

	switch(this->UD){
		case UP:
			if(this->VY > 0) this->VY *= -1;
			break;
		case DOWN:
			if(this->VY < 0) this->VY *= -1;
			break;
		case KEEP:
			break;
	}

	if(this->LR != KEEP || this->UD != KEEP){
		rad = atan2(-this->VY, this->VX) -5*(M_PI/180) + (rand() % 10)*(M_PI/180);

		this->VX = cos(rad)*cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
		this->VY = -sin(rad)*cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
	}

	this->LR = KEEP;
	this->UD = KEEP;

}
