#ifndef		__BALLMGR_H__
#define		__BALLMGR_H__

#include "Player.h"
#include "ScenePlay.h"

class cBall;

class cBallMgr{

private:
	const int BallMax;
	cScenePlay* Parent;
	cPlayer* Player;
	cBall* PlayerBall;
	cBall** ChildBall;
	bool ExistentBall;

public:
	cBallMgr(int ballMax, cScenePlay* parent);
	~cBallMgr();

	void main();

	void CreatePlayerBall(cPlayer* player);
	void CreateFreeBall(double dstX, double dstY, double vx, double vy); 
	void LaunchPlayerBall();
	bool GetExistentBall(){ return this->ExistentBall; }
	unsigned getPowerFlag(){ return this->Parent->getPowerFlag(); }

};

#endif		__BALLMGR_H__