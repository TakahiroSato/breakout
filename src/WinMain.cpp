#include "DxLib.h"
#include "FramerateControl.h"
#include "Keyboard.h"
#include "Debug.h"
#include <math.h>
#include <stdio.h>
#include <time.h>
#include "GameMain.h"
#include "WinMain.h"

const int FPS = 60;

// �v���O������WinMain����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow)
{

	srand(static_cast<unsigned>(time(NULL)));

	ChangeWindowMode(true);						// �E�B���h�E���[�h�ŋN��
	
	SetGraphMode( W_WIDTH , W_HEIGHT , 16 ) ;	// ��ʃ��[�h�̕ύX

	if( DxLib_Init() == -1 )					// DX���C�u��������������
	{
		return -1;								// �G���[���N�����璼���ɏI��
	}

	SetWindowUserCloseEnableFlag( TRUE );		// ���C���E�C���h�E�́~�{�^�������������Ƀ��C�u�����������I�ɃE�C���h�E����邩�ǂ����̃t���O���Z�b�g����i���ݕ���j
	SetDrawScreen(DX_SCREEN_BACK);				// �`���𗠉�ʂɐݒ�


	cFramerateControl *p_frameratecontrol = new cFramerateControl(static_cast<double>(1000/FPS));
	cKeyboard *p_keyboard = new cKeyboard();

#ifdef	DEBUG
	//----------------------------------------
	//�R���\�[���g�p���邽�߂ɕK�v
	AllocConsole();
	freopen("CONOUT$" , "w" , stdout);
	freopen("COUIN$" , "r" , stdin);
	//----------------------------------------
#endif

	cGameMain *p_gamemain = new cGameMain();

	//���C�����[�v
	while(1){
		if(p_frameratecontrol->UpdateFrame()){	
			if( ProcessMessage() == -1 ) break;
			ClearDrawScreen();
			SetBackgroundColor(0,0,0);
			p_keyboard->UpdateKey();
			if(p_keyboard->JustPushKey(KEY_INPUT_ESCAPE)) break;	// Esc�L�[�ŏI��
			
			p_gamemain->main();

			p_frameratecontrol->DrawFrame();

			ScreenFlip();
		}
	}

#ifdef	DEBUG
	//-----------------
	//�R���\�[�����
	FreeConsole();
	//-----------------
#endif	DEBUG

	delete p_frameratecontrol;
	delete p_keyboard;
	delete p_gamemain;

	DxLib_End();						// DX���C�u�����g�p�̏I������

	return 0;							// �\�t�g�̏I��
}