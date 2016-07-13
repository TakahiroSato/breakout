#include "Item.h"
#include "DxLib.h"
#include "GameMain.h"
#include "MyFileIO.h"
#include "WinMain.h"
#include "ItemMgr.h"
#include <stdio.h>
#include <math.h>

int cItem::GHandle = 0;

cItem::cItem(double dstX, double dstY, double vx, double vy, cItemMgr* parent, ItemID ID){

	if(this->GHandle == 0){
		this->GHandle = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "ItemPic").c_str());
	}

	this->X = dstX;
	this->Y = dstY;
	this->VX = vx;
	this->VY = vy;
	this->Parent = parent;
	this->itemID = ID;

	auto set = [=](int* num, char* Name){
		*num = cMyFileIO::GetIntInText("config.txt", Name);
	};

	set(&this->Width, "ItemWidth");
	set(&this->Height, "ItemHeight");
	set(&this->PicWidth, "ItemPicWidth");
	set(&this->PicHeight, "ItemPicHeight");
	switch(this->itemID){
		case this->itemL:
			set(&this->PicSrcX, "ItemPicLX");
			break;
		case this->itemC:
			set(&this->PicSrcX, "ItemPicCX");
			break;
		case this->itemP:
			set(&this->PicSrcX, "ItemPicPX");
			break;
		case this->itemS:
			set(&this->PicSrcX, "ItemPicSX");
			break;
	}
	set(&this->PicSrcY, "ItemPicY");
}

cItem::~cItem(){

}

void cItem::main(){

	this->X += this->VX;
	this->Y += this->VY;

	if(this->Y > W_HEIGHT){
		this->flag = false;
	}

}

void cItem::draw(){
	DrawRectGraph(	static_cast<int>(this->X) , 
					static_cast<int>(this->Y) , 
					this->PicSrcX , this->PicSrcY , this->PicWidth , this->PicHeight ,
					this->GHandle , true , false );
}

void cItem::hitLR(cCharacter* ch, int chNum){
	
	int i = 0;
	double rad = 0;
	double speed = 0;

	switch(this->itemID){
		case this->itemL:
			this->Parent->PlayerAddWidth(30);
			break;
		case this->itemC:
			rad = 225*(M_PI/180);
			speed = cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
			for(i = 0 ; i < 3 ; i++){
				this->Parent->CreateFreeBall(	this->X, this->Y,
												speed*cos(rad), speed*sin(rad));
				rad += 45*(M_PI/180);
			}
			break;
		case this->itemP:
			this->Parent->addPowerFlag(300);
			break;
		case this->itemS:
			this->Parent->addScore(500);
			break;
	}

	this->flag = false;
}

void cItem::hitTB(cCharacter* ch, int chNum){
	
	int i = 0;
	double rad = 0;
	double speed = 0;

	switch(this->itemID){
		case this->itemL:
			this->Parent->PlayerAddWidth(30);
			break;
		case this->itemC:
			rad = 225*(M_PI/180);
			speed = cMyFileIO::GetDoubleInText("config.txt", "BallSpeed");
			for(i = 0 ; i < 3 ; i++){
				this->Parent->CreateFreeBall(	this->X, this->Y,
												speed*cos(rad), speed*sin(rad));
				rad += 45*(M_PI/180);
			}
			break;
		case this->itemP:
			this->Parent->addPowerFlag(300);
			break;
		case this->itemS:
			this->Parent->addScore(500);
			break;
	}

	this->flag = false;
}