#ifndef		__SCENE_H__
#define		__SCENE_H__

class cScene{

private:

public:

	cScene();
	~cScene();

	virtual void main() = 0;
	virtual void draw() = 0;

};

#endif		__SCENE_H__