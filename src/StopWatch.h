#ifndef		__STOPWATCH_H__
#define		__STOPWATCH_H__

class cStopWatch{

private:
	unsigned int mSec;		// �~���b
	unsigned int Sec;		// �b
	unsigned int Minute;	// ��

	unsigned int NowTime;
	unsigned int OldTime;
public:
	cStopWatch();
	~cStopWatch();

	void Update(bool stop);

	unsigned int GetmSec();
	unsigned int GetSec();
	unsigned int GetMinute();
};

#endif		__STOPWATCH_H__