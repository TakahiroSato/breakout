#include "BlockMgr.h"
#include "MyFileIO.h"
#include "Block.h"
#include "WinMain.h"

cBlockMgr::cBlockMgr(int blockMax, cScenePlay* parent)
:BlockMax(blockMax)
{
	int i = 0;

	this->Parent = parent;

	this->ChildBlock = new cBlock*[this->BlockMax];
	
	for(i = 0 ; i < this->BlockMax ; i++){
		this->ChildBlock[i] = NULL;
	}

	this->Map = new unsigned char[this->BlockMax];

	for(i = 0 ; i < this->BlockMax ; i++){
		this->Map[i] = 255;
	}

	this->CS = new CreateStack[this->BlockMax];

	for(i = 0 ; i < this->BlockMax ; i++){
		this->CS[i].Flag = false;
	}

	this->MapWidth = cMyFileIO::GetIntInText("config.txt", "MapWidth");
	this->MapHeight = cMyFileIO::GetIntInText("config.txt", "MapHeight");

	this->ExistentBlock = true;
}

cBlockMgr::~cBlockMgr(){

	SAFE_ARRAY_DELETE(this->ChildBlock);
	SAFE_ARRAY_DELETE(this->Map);
	SAFE_ARRAY_DELETE(this->CS);
}

void cBlockMgr::main(){

	int i = 0, j = 0;

	this->ExistentBlock = false;

	for(i = 0 ; i < this->BlockMax ; i++){
		if(this->ChildBlock[i] != NULL){
			if(this->ChildBlock[i]->flag == false){
				this->ChildBlock[i] = NULL;
			}else if(this->ChildBlock[i]->getBlockNum() != 0){
				this->ExistentBlock = true;
			}
		}
		if(this->CS[i].Flag){
			cBlock* block = new cBlock(this->CS[i].BlockNum, this->CS[i].DstX, 
										this->CS[i].DstY, 0, 0, this);
			for(j = 0 ; j < this->BlockMax ; j++){
				if(this->ChildBlock[j] == NULL){
					this->ChildBlock[j] = block;
					break;
				}
			}
			this->Parent->SignUpChArray(block, this->Parent->CH_BLOCK);
			this->CS[i].Flag = false;
			if(block->getBlockNum() != 0){
				this->ExistentBlock = true;
			}
		}
	}

}

void cBlockMgr::Init(const char* fileName){

	int i = 0, j = 0;
	cBlock* block;

	cMyFileIO::ReadCsv(fileName, this->Map, sizeof(char)*this->BlockMax);

	for(i = 0 ; i < this->BlockMax ; i++){
		if(this->ChildBlock[i] != NULL){
			this->ChildBlock[i]->flag = false;
			this->ChildBlock[i] = NULL;
		}
	}

	for(i = 0 ; i < this->BlockMax ; i++){
		this->CS[i].Flag = false;
	}

	for(i = 0 ; i < this->MapHeight ; i++){
		for(j = 0 ; j < this->MapWidth ; j++){
			unsigned char mapNum = this->Map[this->MapWidth*i+j];
			if(mapNum != 255){
				block = new cBlock(mapNum, 212+55*j, 75+20*i, 0, 0, this);
				this->ChildBlock[this->MapWidth*i+j] = block;
				this->Parent->SignUpChArray(block, this->Parent->CH_BLOCK);
			}
		}
	}

	this->ExistentBlock = true;
}

void cBlockMgr::CreateBlock(unsigned char blockNum, double dstX, double dstY){

	int i = 0;
	for(i = 0 ; i < this->BlockMax ; i++){
		if(this->CS[i].Flag == false){
			this->CS[i].Flag = true;
			this->CS[i].BlockNum = blockNum;
			this->CS[i].DstX = dstX;
			this->CS[i].DstY = dstY;
			break;
		}
	}

}

void cBlockMgr::CreateItem(int dstX, int dstY, int vx, int vy, cItem::ItemID ID){
	this->Parent->CreateItem(dstX, dstY, vx, vy, ID);
}