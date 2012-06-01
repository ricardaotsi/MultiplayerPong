#include "GameState.h"
#include <time.h>
#include <string>
#include <vector>

using namespace std;

GameState::GameState(int w, int h) :
	w(w),
	h(h)
{
	// Inicia bola
	srand(time(NULL));
	bola = new ball(rand()%2, w, h);
	// Inicia jogador 1
	j1 = new paddle(10, h/2-60);
	// Inicia jogador 2
	j2 = new paddle(w-20, h/2-60);
	
}


GameState::~GameState(void)
{
}

void GameState::fromBuffer(char *buffer)
{
	
}

char* GameState::toBuffer(int numJogador)
{
	char temp[512];
	sprintf(temp, "%d;comando:inicia;%s",numJogador,bola->toChar());
	sprintf(temp, "%s%s",temp,j1->toChar("j1"));
	sprintf(temp, "%s%s\n",temp,j2->toChar("j2"));
	return temp;
}

void GameState::update(char *buffer, int numJogador)
{
	//vector<string> cmd;
	char temp[3][20];
	char *pch;
	pch=strtok (buffer,";");
	int j=0;
	while (pch != NULL && j < 3)
	{
		//char tempBuffer[100];
		strcpy(temp[j], pch);
		pch = strtok (NULL, ";");
		j++;
		//cmd.push_back(tempBuffer);
	}
	
	float deltaTime = atof(temp[0]);
	int vel = atoi(temp[1]);
	printf("deltaTime: %f; vel: %d; direcao: %s. \n",deltaTime,vel,temp[2]);
	if(numJogador == 1)
	{
		j1->mover(deltaTime, vel , 600, temp[2]);
	}else{
		j2->mover(deltaTime, vel , 600, temp[2]);
	}
}

void GameState::moverBola(float deltaTime, int vel)
{
	this->bola->mover(deltaTime, vel, j1->posP, j2->posP, this->w, this->h);
}
