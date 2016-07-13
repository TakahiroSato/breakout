#include "WinMain.h"
#include "ScenePlay.h"
#include "DxLib.h"
#include "Keyboard.h"
#include "Player.h"
#include "MyFileIO.h"
#include "GameMain.h"
#include "BallMgr.h"
#include "BlockMgr.h"
#include "ItemMgr.h"
#include "StopWatch.h"
#include "Score.h"
#include "Debug.h"
#include <math.h>

#ifdef	DEBUG
	bool debug_player_hit_flag = true;
#endif

const int cScenePlay::PLAYER_CH_MAX = 10;
const int cScenePlay::BALL_CH_MAX = 1000;
const int cScenePlay::ITEM_CH_MAX = 100;
const int cScenePlay::BLOCK_CH_MAX = cMyFileIO::GetIntInText("config.txt", "MapWidth")*cMyFileIO::GetIntInText("config.txt", "MapHeight");
cCharacter** cScenePlay::ChArray[CH_MAX] = {0}; 
int cScenePlay::GHandleBG = 0;
int cScenePlay::GHandleNumFonts = 0;

cScenePlay::cScenePlay(cSceneGame* parent){

	int i = 0;

	this->Parent = parent;

	// �{�[���}�l�[�W���N���X
	this->BallMgr = new cBallMgr(this->BALL_CH_MAX, this);

	// �u���b�N�}�l�[�W���[�N���X
	this->BlockMgr = new cBlockMgr(this->BLOCK_CH_MAX, this);

	// �A�C�e���}�l�[�W���[�N���X
	this->ItemMgr = new cItemMgr(this->ITEM_CH_MAX, this);

	// �X�R�A�Ǘ��N���X
	this->Score = new cScore();

	// �o�ߎ��Ԍv���p�X�g�b�v�E�H�b�`�N���X
	this->StopWatch = new cStopWatch();

	// CH_MAX�����I�u�W�F�N�g�m��
	this->ChArray[this->CH_PLAYER] = new cCharacter*[PLAYER_CH_MAX];
	this->ChArray[this->CH_BALL] = new cCharacter*[BALL_CH_MAX];
	this->ChArray[this->CH_BLOCK] = new cCharacter*[BLOCK_CH_MAX];
	this->ChArray[this->CH_ITEM] = new cCharacter*[ITEM_CH_MAX];

	//	�m�ۂ����������̃A�h���X��S��NULL�ɂ���///////
	auto f = [=](int num, cScenePlay::ChName chName){
		for(int i = 0 ; i < num ; i++){
			this->ChArray[chName][i] = NULL;
		}
	};

	f(this->PLAYER_CH_MAX, this->CH_PLAYER);
	f(this->BALL_CH_MAX, this->CH_BALL);
	f(this->BLOCK_CH_MAX, this->CH_BLOCK);
	f(this->ITEM_CH_MAX, this->CH_ITEM);
	///////////////////////////////////////////////////

		
	if(this->GHandleBG == 0){
		this->GHandleBG = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "GameBackGround").c_str());
	}

	if(this->GHandleNumFonts == 0){
		this->GHandleNumFonts = cGameMain::GetGHandle(cMyFileIO::GetTextInText("config.txt", "NumFonts").c_str());
	}

	cPlayer* player = new cPlayer(this);
	this->SignUpChArray(player , this->CH_PLAYER);
	this->BallMgr->CreatePlayerBall(player);
	this->BlockMgr->Init(cMyFileIO::GetTextInText("config.txt", "StageZero").c_str());
	this->PowerFlag = 0;
	this->Life = cMyFileIO::GetIntInText("config.txt", "LifeNum");

}

cScenePlay::~cScenePlay(){

	auto f = [=](int num, ChName chName){
		for(int i = 0 ; i < num ; i++){
			SAFE_DELETE(this->ChArray[chName][i]);
		}

		SAFE_ARRAY_DELETE(this->ChArray[chName]);
	};

	f(this->PLAYER_CH_MAX, this->CH_PLAYER);
	f(this->BALL_CH_MAX, this->CH_BALL);
	f(this->BLOCK_CH_MAX, this->CH_BLOCK);
	f(this->ITEM_CH_MAX, this->CH_ITEM);

	// �{�[���}�l�[�W��
	SAFE_DELETE(this->BallMgr);

	// �u���b�N�}�l�[�W��
	SAFE_DELETE(this->BlockMgr);

	// �A�C�e���}�l�[�W��
	SAFE_DELETE(this->ItemMgr);

	// �X�R�A
	SAFE_DELETE(this->Score);

	// �X�g�b�v�E�H�b�`
	SAFE_DELETE(this->StopWatch);

}

void cScenePlay::main(){

	// �|�[�Y�ɑJ��
	if(cKeyboard::JustPushKey(KEY_INPUT_RETURN)){
		this->Parent->SetScene(cSceneGame::SCENE_POSE);
	}

	// �X�e�[�W�N���A�ɑJ��
	if(this->BlockMgr->getExistentBlock() == false){
		this->Parent->SetScene(cSceneGame::SCENE_STAGE_CLEAR);
	}
	// �Q�[���I�[�o�[�J��
	if(this->Life == 0 && !this->BallMgr->GetExistentBall()){
		this->Parent->SetScene(cSceneGame::SCENE_GAMEOVER);
	}

	if(cKeyboard::JustPushKey(KEY_INPUT_SPACE)){
		if(this->Life > 0){
			this->BallMgr->CreatePlayerBall(NULL);
			this->Life--;
		}
		this->LaunchPlayerBall();
	}

#ifdef	DEBUG	
	if(cKeyboard::JustPushKey(KEY_INPUT_D)){
		if(debug_player_hit_flag){
			debug_player_hit_flag = false;
		}else{
			debug_player_hit_flag = true;
		}
	}

	// �A�C�e�����o��
	if(cKeyboard::KeepPushKey(KEY_INPUT_Q)){
		this->ItemMgr->CreateItem(500, 300, 0, 5, cItem::itemL);
	}
	if(cKeyboard::KeepPushKey(KEY_INPUT_W)){
		this->ItemMgr->CreateItem(535, 300, 0, 5, cItem::itemC);
	}
	if(cKeyboard::KeepPushKey(KEY_INPUT_E)){
		this->ItemMgr->CreateItem(570, 300, 0, 5, cItem::itemP);
	}
	if(cKeyboard::KeepPushKey(KEY_INPUT_R)){
		this->ItemMgr->CreateItem(605, 300, 0, 5, cItem::itemS);
	}
#endif

	auto main = [=](int num, ChName chName){
		for(int i = 0 ; i < num ; i++){
			if(this->ChArray[chName][i] != NULL){
				if(this->ChArray[chName][i]->flag){
					this->ChArray[chName][i]->main();
				}else{
					SAFE_DELETE(this->ChArray[chName][i]);
				}
			}
		}
	};

	if(this->PowerFlag > 0){
		this->PowerFlag--;
	}

	this->BlockMgr->main();		// �u���b�N�}�l�[�W��
	this->BallMgr->main();		// �{�[���}�l�[�W��
	this->ItemMgr->main();		// �A�C�e���}�l�[�W��

	main(this->PLAYER_CH_MAX, this->CH_PLAYER);
	main(this->BALL_CH_MAX, this->CH_BALL);
	main(this->BLOCK_CH_MAX, this->CH_BLOCK);
	main(this->ITEM_CH_MAX, this->CH_ITEM);

#ifdef	DEBUG
	if(debug_player_hit_flag){
#endif
	// �o�[�ƃ{�[���̂����蔻��
	this->HitCheckList(	this->ChArray[this->CH_BALL], this->ChArray[this->CH_PLAYER] , 
						this->BALL_CH_MAX , this->PLAYER_CH_MAX, this->CH_BALL, this->CH_PLAYER);
#ifdef	DEBUG
	}
#endif

	// �o�[�ƃ{�[���̂����蔻��
	this->HitCheckList( this->ChArray[this->CH_ITEM], this->ChArray[this->CH_PLAYER],
						this->ITEM_CH_MAX, this->PLAYER_CH_MAX, this->CH_ITEM, this->CH_PLAYER);
	// �{�[���ƃu���b�N�̂����蔻��
	this->HitCheckList( this->ChArray[this->CH_BALL], this->ChArray[this->CH_BLOCK],
						this->BALL_CH_MAX, this->BLOCK_CH_MAX, this->CH_BALL, this->CH_BLOCK);

	// �X�R�A�}�l�[�W��
	this->Score->main();
}

void cScenePlay::draw(){

	unsigned FontsWidth = cMyFileIO::GetIntInText("config.txt", "NumFontsWidth");
	unsigned FontsHeight = cMyFileIO::GetIntInText("config.txt", "NumFontsHeight");

	// �w�i�`��
	DrawRectGraph(0, 0, 0, 0, 800, 600, this->GHandleBG, true, false);

	auto draw = [=](int num, ChName chName){
		for(int i = 0 ; i < num ; i++){
			if(this->ChArray[chName][i] != NULL){
				this->ChArray[chName][i]->draw();
			}
		}
	};

	draw(this->PLAYER_CH_MAX, this->CH_PLAYER);
	draw(this->BLOCK_CH_MAX, this->CH_BLOCK);
	draw(this->BALL_CH_MAX, this->CH_BALL);
	draw(this->ITEM_CH_MAX, this->CH_ITEM);

	// ���x���`��
	DrawRectGraph(	175-8-FontsWidth, 25+10, 
					FontsWidth*static_cast<unsigned>(this->Parent->getStageNo()+1), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);

	// �o�ߎ��ԕ`��
	// �~���b
	DrawRectGraph(	167-FontsWidth, 155, 
					FontsWidth*static_cast<unsigned>((this->StopWatch->GetmSec()/10)%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*2, 155, 
					FontsWidth*static_cast<unsigned>(this->StopWatch->GetmSec()/100), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	// �b
	DrawRectGraph(	154-FontsWidth*3, 155, 
					FontsWidth*static_cast<unsigned>(this->StopWatch->GetSec()%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	154-FontsWidth*4, 155, 
					FontsWidth*static_cast<unsigned>(this->StopWatch->GetSec()/10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	// ��
	DrawRectGraph(	141-FontsWidth*5, 155, 
					FontsWidth*static_cast<unsigned>(this->StopWatch->GetMinute()%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	141-FontsWidth*6, 155, 
					FontsWidth*static_cast<unsigned>(this->StopWatch->GetMinute()/10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);

	// �c�@�`��
	DrawRectGraph(	175-8-FontsWidth*3, 600-25-10-FontsHeight, 
					FontsWidth*static_cast<unsigned>((this->Life/100)%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	175-8-FontsWidth*2, 600-25-10-FontsHeight, 
					FontsWidth*static_cast<unsigned>((this->Life/10)%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	175-8-FontsWidth, 600-25-10-FontsHeight, 
					FontsWidth*static_cast<unsigned>(this->Life%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);

	// �X�R�A�`��
	DrawRectGraph(	167-FontsWidth, 238, 
					FontsWidth*static_cast<unsigned>(this->Score->getScore()%10), 
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*2, 238,
					FontsWidth*static_cast<unsigned>((this->Score->getScore()/10)%10),
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*3, 238,
					FontsWidth*static_cast<unsigned>((this->Score->getScore()/100)%10),
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*4, 238,
					FontsWidth*static_cast<unsigned>((this->Score->getScore()/1000)%10),
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*5, 238,
					FontsWidth*static_cast<unsigned>((this->Score->getScore()/10000)%10),
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
	DrawRectGraph(	167-FontsWidth*6, 238,
					FontsWidth*static_cast<unsigned>((this->Score->getScore()/100000)%10),
					0, FontsWidth, FontsHeight, this->GHandleNumFonts, true, false);
}

// �L�����N�^�[���X�g���m�̓����蔻��
void cScenePlay::HitCheckList(cCharacter** pch1 , cCharacter** pch2 , int size1 , int size2, int chNum1, int chNum2){

	int i = 0 , j = 0;
	double rad = 0;
	bool HitFlag = false;

	for( i = 0 ; i < size1 ; i++ ){
		for( j = 0 ; j < size2 ; j++ ){
			if( *(pch1+i) != NULL && *(pch2+j) != NULL ){
				if( (*(pch1+i))->flag && (*(pch2+j))->flag ){ 
			
					rad = atan2(-pch1[i]->VY, pch1[i]->VX);

					// �߂荞�݊m�F
					while(	pch1[i]->X+pch1[i]->Width		> pch2[j]->X+pch2[j]->VX &&
							pch1[i]->X						< pch2[j]->X+pch2[j]->Width &&
							pch1[i]->Y+pch1[i]->Height		> pch2[j]->Y+pch2[j]->VY &&
							pch1[i]->Y						< pch2[j]->Y+pch2[j]->Height  ){
							
							HitFlag = true;

							pch1[i]->X -= cos(rad);
							pch1[i]->Y += sin(rad);
					}

					if(HitFlag){
						if(	pch1[i]->X+pch1[i]->Width <= pch2[j]->X ||
							pch1[i]->X >= pch2[j]->X+pch2[j]->Width){
								(*(pch1+i))->hitLR(pch2[j], chNum2);
								(*(pch2+j))->hitLR(pch1[i], chNum1);
						}else{
							(*(pch1+i))->hitTB(pch2[j], chNum2);
							(*(pch2+j))->hitTB(pch1[i], chNum1);
						}
					}

					HitFlag = false;
				}
			}
		}
	}

}

// �L�����N�^�[���X�g�ɃL�����o�^
cCharacter* cScenePlay::SignUpChArray(cCharacter* pch , ChName chno){

	int i = 0;
	int max = 0;

	switch(chno){

	case CH_PLAYER:
		max = PLAYER_CH_MAX;
		break;
	case CH_BALL:
		max = BALL_CH_MAX;
		break;
	case CH_BLOCK:
		max = BLOCK_CH_MAX;
		break;
	case CH_ITEM:
		max = ITEM_CH_MAX;
		break;
	default:
		max = 0;

	};

	for( i = 0 ; i < max ; i++ ){
		if( ChArray[chno][i] == NULL ){
			ChArray[chno][i] = pch;
			return ChArray[chno][i];
		}
	}

	return NULL;

}

// �v���C���[�̃{�[���i�o�[�ɂ������Ă�j����
void cScenePlay::LaunchPlayerBall(){

	this->BallMgr->LaunchPlayerBall();

}

// �t���[�̃{�[������
void cScenePlay::CreateFreeBall(double dstX, double dstY, double vx, double vy){

	this->BallMgr->CreateFreeBall(dstX, dstY, vx, vy);
}

// �o�[�̕����₷
void cScenePlay::PlayerAddWidth(int addWidth){

	int i = 0;

	for(i = 0 ; i < this->PLAYER_CH_MAX ; i++){
		if(this->ChArray[this->CH_PLAYER][i] != NULL){
			reinterpret_cast<cPlayer*>(this->ChArray[this->CH_PLAYER][i])->addWidth(addWidth);
		}
	}
}

// �A�C�e������
void cScenePlay::CreateItem(int dstX, int dstY, int vx, int vy, cItem::ItemID ID){
	this->ItemMgr->CreateItem(dstX, dstY, vx, vy, ID);
}

// �X�R�A�ǉ�
void cScenePlay::addScore(unsigned Score){
	this->Score->addScore(Score);
}

// �X�R�A�̒l�擾
unsigned cScenePlay::getScore(){
	return this->Score->getScore();
}


void cScenePlay::StopWatchUpdate(bool stop){

	this->StopWatch->Update(stop);

}

// �X�e�[�W�ύX
void cScenePlay::ChangeStage(const char* mapName){
	this->BlockMgr->Init(mapName);
}