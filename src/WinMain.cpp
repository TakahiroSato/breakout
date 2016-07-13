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

// プログラムはWinMainから始まります
int WINAPI WinMain(HINSTANCE hInstance , HINSTANCE hPrevInstance , LPSTR lpCmdLine , int nCmdShow)
{

	srand(static_cast<unsigned>(time(NULL)));

	ChangeWindowMode(true);						// ウィンドウモードで起動
	
	SetGraphMode( W_WIDTH , W_HEIGHT , 16 ) ;	// 画面モードの変更

	if( DxLib_Init() == -1 )					// DXライブラリ初期化処理
	{
		return -1;								// エラーが起きたら直ちに終了
	}

	SetWindowUserCloseEnableFlag( TRUE );		// メインウインドウの×ボタンを押した時にライブラリが自動的にウインドウを閉じるかどうかのフラグをセットする（現在閉じる）
	SetDrawScreen(DX_SCREEN_BACK);				// 描画先を裏画面に設定


	cFramerateControl *p_frameratecontrol = new cFramerateControl(static_cast<double>(1000/FPS));
	cKeyboard *p_keyboard = new cKeyboard();

#ifdef	DEBUG
	//----------------------------------------
	//コンソール使用するために必要
	AllocConsole();
	freopen("CONOUT$" , "w" , stdout);
	freopen("COUIN$" , "r" , stdin);
	//----------------------------------------
#endif

	cGameMain *p_gamemain = new cGameMain();

	//メインループ
	while(1){
		if(p_frameratecontrol->UpdateFrame()){	
			if( ProcessMessage() == -1 ) break;
			ClearDrawScreen();
			SetBackgroundColor(0,0,0);
			p_keyboard->UpdateKey();
			if(p_keyboard->JustPushKey(KEY_INPUT_ESCAPE)) break;	// Escキーで終了
			
			p_gamemain->main();

			p_frameratecontrol->DrawFrame();

			ScreenFlip();
		}
	}

#ifdef	DEBUG
	//-----------------
	//コンソール解放
	FreeConsole();
	//-----------------
#endif	DEBUG

	delete p_frameratecontrol;
	delete p_keyboard;
	delete p_gamemain;

	DxLib_End();						// DXライブラリ使用の終了処理

	return 0;							// ソフトの終了
}