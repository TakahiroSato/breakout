#include "WinMain.h"
#include "ItemMgr.h"
#include "Item.h"
#include "WinMain.h"
#include "MyFileIO.h"


cItemMgr::cItemMgr(int itemMax, cScenePlay* parent)
:ItemMax(itemMax)
{

	int i = 0;

	this->Parent = parent;

	this->ChildItem = new cItem*[this->ItemMax];

	for(i = 0 ; i < this->ItemMax ; i++){
		this->ChildItem[i] = NULL;
	}

}

cItemMgr::~cItemMgr(){
	SAFE_ARRAY_DELETE(this->ChildItem);
}

void cItemMgr::main(){

	int i = 0;

	for(i = 0 ; i < this->ItemMax ; i++){
		if(this->ChildItem[i] != NULL){
			if(this->ChildItem[i]->flag == false){
				this->ChildItem[i] = NULL;
			}
		}
	}

}

void cItemMgr::CreateItem(double dstX, double dstY, double vx, double vy, cItem::ItemID ID){

	int i = 0;

	cItem* item = new cItem(dstX, dstY, vx, vy, this, ID);

	for(i = 0 ; i < this->ItemMax ; i++){
		if(this->ChildItem[i] == NULL){
			this->ChildItem[i] = item;
			break;
		}
	}

	this->Parent->SignUpChArray(item, this->Parent->CH_ITEM);
}

void cItemMgr::PlayerAddWidth(int addWidth){ 

	this->Parent->PlayerAddWidth(addWidth);
}

void cItemMgr::addScore(unsigned Score){
	this->Parent->addScore(Score);
}

void cItemMgr::addPowerFlag(unsigned additionalPower){
	this->Parent->addPowerFlag(additionalPower);
}

void cItemMgr::CreateFreeBall(double dstX, double dstY, double vx, double vy){
	this->Parent->CreateFreeBall(dstX, dstY, vx, vy);
}