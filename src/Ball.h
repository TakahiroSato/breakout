#ifndef		__BALL_H__
#define		__BALL_H__

#include "Character.h"
#include "BallMgr.h"

class cBall : public cCharacter{

public:
	typedef enum tagDirection{
		KEEP,
		RIGHT,
		LEFT,
		UP,
		DOWN
	}Direction;

private:
	static int GHandle;
	static int SHandleHit;
	cBallMgr* Parent;
	Direction LR;
	Direction UD;

public:

	cBall(double dstX, double dstY, double vx, double vy, cBallMgr* parent);
	~cBall();

	void main();
	void draw();
	void hitLR(cCharacter* ch, int chNum);
	void hitTB(cCharacter* ch, int chNum);

	void MoveDirection(Direction lr, Direction ud);
	void MoveSet();

};

#endif		__BALL_H__