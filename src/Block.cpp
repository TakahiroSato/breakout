#include "DxLib.h"
#include "Block.h"
#include "BlockMgr.h"
#include "MyFileIO.h"
#include "Ball.h"

int cBlock::GHandle = 0;

cBlock::cBlock(unsigned char blockNum, double dstX, double dstY, double vx, double vy, cBlockMgr* parent){

	this->Parent = parent;

	if(this->GHandle == 0){
		this->GHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "BlockPic").c_str());
	}

	this->BlockNum = blockNum;

	this->X = dstX;
	this->Y = dstY;
	this->VX = vx;
	this->VY = vy;
	
	auto set = [=](int* num, char* Name){
		*num = cMyFileIO::GetIntInText("config.txt", Name);
	};

	set(&this->Width, "BlockWidth");
	set(&this->Height, "BlockHeight");
	set(&this->PicWidth, "BlockPicWidth");
	set(&this->PicHeight, "BlockPicHeight");
	
	switch(this->BlockNum){
		case 0:
			set(&this->PicSrcX, "BlockPicZeroX");
			set(&this->PicSrcY, "BlockPicZeroY");
			break;
		case 1:
			set(&this->PicSrcX, "BlockPicOneX");
			set(&this->PicSrcY, "BlockPicOneY");
			break;
		case 2:
			set(&this->PicSrcX, "BlockPicTwoX");
			set(&this->PicSrcY, "BlockPicTwoY");
			break;
		case 3:
			set(&this->PicSrcX, "BlockPicThreeX");
			set(&this->PicSrcY, "BlockPicThreeY");
			break;
	}
}

cBlock::~cBlock(){

}

void cBlock::main(){
	this->X += this->VX;
	this->Y += this->VY;
}

void cBlock::draw(){
	DrawRectGraph(	static_cast<int>(this->X) , 
					static_cast<int>(this->Y) , 
					this->PicSrcX , this->PicSrcY , this->PicWidth , this->PicHeight ,
					this->GHandle , true , false );
}

void cBlock::hitLR(cCharacter* ch, int chNum){
	
	int BallFlag = 0;
	cBall* ball = NULL;

	if(chNum == cScenePlay::CH_BALL){
		BallFlag = 1;
	}
	
	switch(this->BlockNum){
		case 0:	// 壊れない
			break;
		case 1: // 赤
			this->flag = false;
			if(this->Parent->getPowerFlag() > 0){
				if( rand()%10 == 0){
					this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
				}
				this->Parent->addScore(500);
				break;
			}
			this->Parent->CreateBlock(2, this->X, this->Y);
			break;
		case 2: // 肌色
			this->flag = false;
			if(this->Parent->getPowerFlag() > 0){
				if( rand()%10 == 0){
					this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
				}
				this->Parent->addScore(250);
				break;
			}
			this->Parent->CreateBlock(3, this->X, this->Y);
			break;
		case 3: // 白
			this->flag = false;
			BallFlag = 0;
			// アイテム
			if( rand()%10 == 0){
				this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
			}
			this->Parent->addScore(100);
			break;
	}

	if(BallFlag){
		if(this->Parent->getPowerFlag() == 0 || this->BlockNum == 0){
			ball = dynamic_cast<cBall*>(ch);
			if(ball != NULL){	
				if(ch->VX > 0){
					ball->MoveDirection(cBall::LEFT, cBall::KEEP);
				}else{
					ball->MoveDirection(cBall::RIGHT, cBall::KEEP);
				}
			}
		}
	}
}

void cBlock::hitTB(cCharacter* ch, int chNum){
	
	int BallFlag = 0;
	cBall* ball = NULL;

	if(chNum == cScenePlay::CH_BALL){
		BallFlag = 1;
	}

	switch(this->BlockNum){
		case 0:	// 壊れない
			break;
		case 1: // 赤
			this->flag = false;
			if(this->Parent->getPowerFlag() > 0){
				if( rand()%10 == 0){
					this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
				}
				this->Parent->addScore(500);
				break;
			}
			this->Parent->CreateBlock(2, this->X, this->Y);
			break;
		case 2: // 肌色
			this->flag = false;
			if(this->Parent->getPowerFlag() > 0){
				if( rand()%10 == 0){
					this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
				}
				this->Parent->addScore(250);
				break;
			}
			this->Parent->CreateBlock(3, this->X, this->Y);
			break;
		case 3: // 白
			this->flag = false;
			BallFlag = 0;
			if( rand()%10 == 0){
				this->Parent->CreateItem(this->X+10, this->Y, 0, 2.0, static_cast<cItem::ItemID>(rand()%(cItem::itemS+1)));
			}
			this->Parent->addScore(100);
			break;
	}

	if(BallFlag){
		if(this->Parent->getPowerFlag() == 0 || this->BlockNum == 0){
			ball = dynamic_cast<cBall*>(ch);
			if(ball != NULL){	
				if(ch->VY > 0){
					ball->MoveDirection(cBall::KEEP, cBall::UP);
				}else{
					ball->MoveDirection(cBall::KEEP, cBall::DOWN);
				}
			}
		}
	}

}