#pragma once
#include "ball.h"
#include "paddle.h"

class GameState
{
private:
	
public:
	ball* bola;
	paddle* j1;
	paddle* j2;
	int numJogador;
	GameState();
	~GameState(void);
	char* toBuffer();
	void fromBuffer( char cmd[8][100]);
	void update();
	int separar( char pos[100]);
};

