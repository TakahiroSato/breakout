#ifndef		__BLOCK_H__
#define		__BLOCK_H__

#include "Character.h"

class cBlockMgr;

class cBlock : public cCharacter{

private:
	
	static int GHandle;
	cBlockMgr* Parent;
	unsigned char BlockNum;

public:

	cBlock(unsigned char blockNum, double dstX, double dstY, double vx, double vy, cBlockMgr* parent);
	~cBlock();

	void main();
	void draw();
	void hitLR(cCharacter* ch, int chNum);
	void hitTB(cCharacter* ch, int chNum);
	unsigned char getBlockNum(){ return this->BlockNum; }

};

#endif		__BLOCK_H__