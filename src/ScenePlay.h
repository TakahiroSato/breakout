#ifndef		__SCENEPLAY_H__
#define		__SCENEPLAY_H__

#include "Scene.h"
#include "Character.h"
#include "Game.h"
#include "Item.h"

class cBallMgr;
class cBlockMgr;
class cItemMgr;
class cScore;
class cStopWatch;

class cScenePlay : public cScene{

private:
	static const int PLAYER_CH_MAX;
	static const int BALL_CH_MAX;
	static const int BLOCK_CH_MAX;
	static const int ITEM_CH_MAX;
	static cCharacter* (*ChArray[]);
	cSceneGame* Parent;
	cBallMgr*	BallMgr;
	cBlockMgr*	BlockMgr;
	cItemMgr*	ItemMgr;
	cScore*		Score;
	cStopWatch* StopWatch;
	static int GHandleBG;
	static int GHandleNumFonts;
	int Life;
	unsigned PowerFlag;

public:

	typedef enum tagChName{
		CH_PLAYER ,
		CH_BALL,
		CH_BLOCK,
		CH_ITEM,
		CH_MAX
	}ChName;

	cScenePlay(cSceneGame* parent);
	~cScenePlay();

	void main();
	void draw();

	void HitCheckList(cCharacter** , cCharacter** , int , int, int, int);

	static cCharacter* SignUpChArray(cCharacter* , ChName);

	void LaunchPlayerBall();
	void CreateItem(int dstX, int dstY, int vx, int vy, cItem::ItemID ID);
	void CreateFreeBall(double dstX, double dstY, double vx, double vy);

	// バーの幅増やす
	void PlayerAddWidth(int addWidth);
	
	// 貫通
	unsigned getPowerFlag(){ return this->PowerFlag; }
	void addPowerFlag(unsigned additionalPower){ this->PowerFlag += additionalPower; }

	// スコア増やす
	void addScore(unsigned Score);
	unsigned getScore();
	void StopWatchUpdate(bool stop);

	void ChangeStage(const char* mapName);
};

#endif		__SCENEPLAY_H__