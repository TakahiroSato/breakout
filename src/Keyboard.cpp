#include <Windows.h>
#include "DxLib.h"
#include "Keyboard.h"

char cKeyboard::keyarray[256] = {0};

cKeyboard::cKeyboard(){
	ZeroMemory(&keyarray[0],sizeof(char)*256);
}

cKeyboard::~cKeyboard(){}

void cKeyboard::UpdateKey(){

	int i = 0;

	for( i = 0 ; i < 256 ; i++ ){
		keyarray[i] <<= 1;
		if( CheckHitKey(i) ) keyarray[i] |= 1;
	}
}

bool cKeyboard::JustPushKey(int keycode){
	
	if( (keyarray[keycode] & 1) && !(keyarray[keycode] & 2) ){
		return true;
	}else{
		return false;
	}
}

bool cKeyboard::JustUpKey(int keycode){

	if( !(keyarray[keycode] & 1) && (keyarray[keycode] & 2) ){
		return true;
	}else{
		return false;
	}
}

bool cKeyboard::KeepPushKey(int keycode){
	
	if( (keyarray[keycode] & 1) && (keyarray[keycode] & 2) ){
		return true;
	}else{
		return false;
	}
}

bool cKeyboard::KeepUpKey(int keycode){

	if( !(keyarray[keycode] & 1) && !(keyarray[keycode] & 2) ){
		return true;
	}else{
		return false;
	}
}