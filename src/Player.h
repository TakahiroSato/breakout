#ifndef		__PLAYER_H__
#define		__PLAYER_H__

#include "Character.h"

class cScenePlay;

class cPlayer : public cCharacter{

private:
	static int GHandle;
	cScenePlay* Parent;
	int origWidth;
	float additionalWidth;

public:
	cPlayer(cScenePlay* parent);
	~cPlayer();

	void main();
	void draw();
	void hitLR(cCharacter* ch, int chNum);
	void hitTB(cCharacter* ch, int chNum);

	void addWidth(int addWidth);
};

#endif		__PLAYER_H__