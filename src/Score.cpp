#include "Score.h"

cScore::cScore(){
	this->score = 0;
	this->additionalScore = 0;
}

cScore::~cScore(){

}

void cScore::main(){

	if(this->additionalScore >= 10){
		this->score += static_cast<unsigned>(this->additionalScore/10);
		this->additionalScore -= static_cast<unsigned>(this->additionalScore/10);
	}else if(this->additionalScore > 0){
		this->score++;
		this->additionalScore--;
	}

	if(this->score > 999999){
		this->score = 999999;
	}

}

void cScore::addScore(unsigned addScore){
	this->additionalScore += addScore;
}