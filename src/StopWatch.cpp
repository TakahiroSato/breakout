#include "StopWatch.h"
#include <Windows.h>
#include <iostream>
#include <stdlib.h>
#include <mmsystem.h>
#include <time.h>

#pragma comment(lib,"winmm.lib")

cStopWatch::cStopWatch(){

	this->mSec		= 0;
	this->Sec		= 0;
	this->Minute	= 0;

	this->NowTime = timeGetTime();
	this->OldTime = NowTime;

}

cStopWatch::~cStopWatch(){

}

void cStopWatch::Update(bool stop){

	this->NowTime = timeGetTime();

	if(!stop){
		this->mSec += this->NowTime-this->OldTime;

		if(this->mSec >= 1000){	// 1000ミリ秒(1秒）経ってたら
			this->mSec -= 1000;
			this->Sec++;
		}

		if(this->Sec >= 60){	// 60秒（1分）経ってたら
			this->Sec -= 60;
			this->Minute++;
		}
	}

	this->OldTime = this->NowTime;
}

unsigned int cStopWatch::GetmSec(){return this->mSec;}
unsigned int cStopWatch::GetSec(){return this->Sec;}
unsigned int cStopWatch::GetMinute(){return this->Minute;}