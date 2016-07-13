#ifndef		__ITEMMGR_H__
#define		__ITEMMGR_H__

#include "ScenePlay.h"
#include "Item.h"

class cItemMgr{

private:
	const int ItemMax;
	cScenePlay* Parent;
	cItem** ChildItem;

public:
	cItemMgr(int itemMax, cScenePlay* parent);
	~cItemMgr();

	void main();

	void CreateItem(double dstX, double dstY, double vx, double vy, cItem::ItemID ID); 
	void PlayerAddWidth(int addWidth);
	void addScore(unsigned Score);
	void CreateFreeBall(double dstX, double dstY, double vx, double vy);
	void addPowerFlag(unsigned additionalPower);
};

#endif		__ITEMMGR_H__