#ifndef		__CHARACTER_H__
#define		__CHARACTER_H__

class cCharacter{

private:
public:
	double X;			// ��ʏ�ł�X���W
	double Y;			// ��ʏ�ł�Y���W
	double VX;			// �����ړ���
	double VY;			// �c���ړ���
	int Width;			// �����蔻��p�̉���
	int Height;			// �����蔻��p�̏c��
	int PicWidth;		// �`�悷��G�̉���
	int PicHeight;		// �`�悷��G�̏c��
	int PicSrcX;		// �`�悷��G�̃t�@�C���̕`��X���W
	int PicSrcY;		// �`�悷��G�̃t�@�C���̕`��Y���W
	bool flag;			// �g�p�t���O�i�g�p�F1�@�g�p����Ă��Ȃ��F0�j

	cCharacter();
	~cCharacter();

	virtual void main() = 0;
	virtual void draw() = 0;
	virtual void hitLR(cCharacter* ch, int chNum) = 0;
	virtual void hitTB(cCharacter* ch, int chNum) = 0;
};

#endif		__CHARACTER_H__