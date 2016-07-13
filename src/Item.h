#ifndef		__ITEM_H__
#define		__ITEM_H__

#include "Character.h"

class cItemMgr;

class cItem : public cCharacter{

private:
	static int GHandle;
	cItemMgr* Parent;
	int	itemID;

public:
	typedef enum tagItemID{
		itemL,
		itemC,
		itemP,
		itemS
	}ItemID;

	cItem(double dstX, double dstY, double vx, double vy, cItemMgr* parent, ItemID ID);
	~cItem();

	void main();
	void draw();
	void hitLR(cCharacter* ch, int chNum);
	void hitTB(cCharacter* ch, int chNum);

};
#endif		__ITEM_H__