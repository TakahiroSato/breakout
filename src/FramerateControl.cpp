#include "FramerateControl.h"
#include "DxLib.h"
#include <iostream>
#include <stdlib.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

unsigned int cFramerateControl::oldtime = 0;
unsigned int cFramerateControl::oldtime2 = 0;
unsigned int cFramerateControl::newtime = 0;

// コンストラクタ
// 引数ミリ秒
cFramerateControl::cFramerateControl(double updatetime)
:updatetime(updatetime){
	this->oldtime = GetNowCount();
	this->oldtime2 = GetNowCount();
	this->newtime = GetNowCount();
	this->cnt1 = 0;
	this->cnt2 = 0;

	// 最小分解能を1ミリ秒に設定
	//if( timeBeginPeriod(1) != TIMERR_NOERROR ) printf("最小分解能の設定に失敗\n");
}

// デストラクタ
cFramerateControl::~cFramerateControl(){
	
}

// FPS制御
bool cFramerateControl::UpdateFrame(){

	this->newtime = timeGetTime();								// 現在時間取得
	if( this->newtime - this->oldtime2 >= 1000 ){				
		this->cnt2 = this->cnt1;
		this->cnt1 = 0;
		this->oldtime2 = this->newtime;
	}
	if( static_cast<double>(this->newtime - this->oldtime) >= this->updatetime ){
		this->oldtime = this->newtime;
		this->cnt1++;
		return true;
	}

	return false;
}

// FPS描画
void cFramerateControl::DrawFrame(){

	char p[256] = {0};

	DrawString(0 , 0 , itoa(this->cnt1 , p , 10) , GetColor(255,0,255)); 
	DrawString(0 , 20 , itoa(this->cnt2 , p , 10) , GetColor(255,0,255));

}