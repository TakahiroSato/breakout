#ifndef		__BLOCKMGR_H__
#define		__BLOCKMGR_H__

#include "ScenePlay.h"
#include "Item.h"

class cBlock;

class cBlockMgr{

private:

	typedef struct tagCreateStack{
		bool Flag;
		unsigned char BlockNum;
		double DstX;
		double DstY;
	}CreateStack, *LPCreateStack;

	cScenePlay* Parent;
	const int BlockMax;
	cBlock** ChildBlock;
	unsigned char *Map;
	int MapWidth;
	int MapHeight;
	LPCreateStack CS;
	bool ExistentBlock;

public:
	
	cBlockMgr(int blockMax, cScenePlay* parent);
	~cBlockMgr();

	void Init(const char* fileName);

	void main();

	void CreateBlock(unsigned char blockNum, double dstX, double dstY); 
	void CreateItem(int dstX, int dstY, int vx, int vy, cItem::ItemID ID);
	bool getExistentBlock(){ return this->ExistentBlock; }
	unsigned getPowerFlag(){ return this->Parent->getPowerFlag(); }
	void addScore(unsigned Score){ this->Parent->addScore(Score); }
};

#endif		__BLOCKMGR_H__