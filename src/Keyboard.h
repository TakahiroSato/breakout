#ifndef	__KEYBOARD_H__
#define __KEYBOARD_H__

class cKeyboard{

private:
	static char keyarray[256];

public:
	cKeyboard();
	~cKeyboard();

	static void UpdateKey();
	static bool JustPushKey(int);
	static bool JustUpKey(int);
	static bool KeepPushKey(int);
	static bool KeepUpKey(int);

};

#endif	__KEYBOARD_H__