#ifndef	__FRAMERATECONTROL_H__
#define	__FRAMERATECONTROL_H__

class cFramerateControl{

private:
	static unsigned int oldtime;
	static unsigned int oldtime2;
	static unsigned int newtime;
	const double updatetime;
	int cnt1 , cnt2;
public:
	cFramerateControl(double);
	~cFramerateControl();

	bool UpdateFrame();
	void DrawFrame();

};

#endif	__FRAMERATECONTROL_H__