#pragma once
#include "ball.h"
#include "paddle.h"

class GameState
{
private:
	ball* bola;
	paddle* j1;
	paddle* j2;
	
public:
	GameState(int w, int h);
	~GameState(void);
	char* toBuffer();
	void fromBuffer();
	void update();
};

