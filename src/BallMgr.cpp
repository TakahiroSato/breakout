#include "WinMain.h"
#include "BallMgr.h"
#include "Ball.h"
#include "WinMain.h"
#include "MyFileIO.h"

cBallMgr::cBallMgr(int ballMax, cScenePlay* parent)
:BallMax(ballMax)
{
	this->Player = NULL;
	this->Parent = parent;

	this->ChildBall = new cBall*[this->BallMax-1];
	for(int i = 0 ; i < this->BallMax-1 ; i++){
		this->ChildBall[i] = NULL;
	}

	this->PlayerBall = NULL;
	this->ExistentBall = true;
}

cBallMgr::~cBallMgr(){
	SAFE_ARRAY_DELETE(this->ChildBall);
}

void cBallMgr::main(){

	int i = 0;

	this->ExistentBall = false;

	if(this->PlayerBall != NULL){
		this->PlayerBall->X = this->Player->X + this->Player->Width/2 - this->PlayerBall->Width/2;
		this->PlayerBall->Y = this->Player->Y - this->PlayerBall->Height-1;
		this->ExistentBall = true;
	}

	for(i = 0 ; i < this->BallMax-1 ; i++){
		if(this->ChildBall[i] != NULL){

			if(this->ChildBall[i]->flag == false){
				this->ChildBall[i] = NULL;
			}

			this->ExistentBall = true;

		}
	}

}

void cBallMgr::CreateFreeBall(double dstX, double dstY, double vx, double vy){

	int i = 0;

	cBall* ball = new cBall(dstX, dstY, vx, vy, this);

	for(i = 0 ; i < this->BallMax-1 ; i++){
		if(this->ChildBall[i] == NULL){
			this->ChildBall[i] = ball;
			break;
		}
	}

	this->Parent->SignUpChArray(ball, this->Parent->CH_BALL);

}

void cBallMgr::CreatePlayerBall(cPlayer* player){
	
	if(this->Player == NULL){
		this->Player = player;
	}

	if(this->PlayerBall == NULL){
		cBall* ball = new cBall(this->Player->X+this->Player->Width/2, this->Player->Y-15, this->Player->VX, this->Player->VY, this);
		this->PlayerBall = ball;
		this->Parent->SignUpChArray(ball, this->Parent->CH_BALL);
	}

}

void cBallMgr::LaunchPlayerBall(){

	if(this->PlayerBall != NULL){
		this->CreateFreeBall(this->PlayerBall->X, this->PlayerBall->Y, 0, -cMyFileIO::GetDoubleInText("config.txt", "BallSpeed"));
		
		this->PlayerBall->flag = false;
		this->PlayerBall = NULL;
	}

}
		