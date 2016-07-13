#include "FramerateControl.h"
#include "DxLib.h"
#include <iostream>
#include <stdlib.h>
#include <mmsystem.h>

#pragma comment(lib,"winmm.lib")

unsigned int cFramerateControl::oldtime = 0;
unsigned int cFramerateControl::oldtime2 = 0;
unsigned int cFramerateControl::newtime = 0;

// �R���X�g���N�^
// �����~���b
cFramerateControl::cFramerateControl(double updatetime)
:updatetime(updatetime){
	this->oldtime = GetNowCount();
	this->oldtime2 = GetNowCount();
	this->newtime = GetNowCount();
	this->cnt1 = 0;
	this->cnt2 = 0;

	// �ŏ�����\��1�~���b�ɐݒ�
	//if( timeBeginPeriod(1) != TIMERR_NOERROR ) printf("�ŏ�����\�̐ݒ�Ɏ��s\n");
}

// �f�X�g���N�^
cFramerateControl::~cFramerateControl(){
	
}

// FPS����
bool cFramerateControl::UpdateFrame(){

	this->newtime = timeGetTime();								// ���ݎ��Ԏ擾
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

// FPS�`��
void cFramerateControl::DrawFrame(){

	char p[256] = {0};

	DrawString(0 , 0 , itoa(this->cnt1 , p , 10) , GetColor(255,0,255)); 
	DrawString(0 , 20 , itoa(this->cnt2 , p , 10) , GetColor(255,0,255));

}