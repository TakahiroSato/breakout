#ifndef		__CHARACTER_H__
#define		__CHARACTER_H__

class cCharacter{

private:
public:
	double X;			// 画面上でのX座標
	double Y;			// 画面上でのY座標
	double VX;			// 横軸移動量
	double VY;			// 縦軸移動量
	int Width;			// 当たり判定用の横幅
	int Height;			// 当たり判定用の縦幅
	int PicWidth;		// 描画する絵の横幅
	int PicHeight;		// 描画する絵の縦幅
	int PicSrcX;		// 描画する絵のファイルの描画X座標
	int PicSrcY;		// 描画する絵のファイルの描画Y座標
	bool flag;			// 使用フラグ（使用：1　使用されていない：0）

	cCharacter();
	~cCharacter();

	virtual void main() = 0;
	virtual void draw() = 0;
	virtual void hitLR(cCharacter* ch, int chNum) = 0;
	virtual void hitTB(cCharacter* ch, int chNum) = 0;
};

#endif		__CHARACTER_H__