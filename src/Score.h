#ifndef		__SCORE_H__
#define		__SCORE_H__

class cScore{

private:
	unsigned score;
	unsigned additionalScore;

public:
	cScore();
	~cScore();

	void main();
	unsigned getScore(){ return this->score; }
	void addScore(unsigned addScore);
};

#endif		__SCORE_H__