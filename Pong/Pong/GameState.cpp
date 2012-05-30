#include "GameState.h"
#include <string>
GameState::GameState()
{
	bola = new ball();
	j1 = new paddle();
	j2 = new paddle();
	numJogador=0;
}


GameState::~GameState(void)
{
}

void GameState::fromBuffer( char cmd[8][100])
{
	numJogador=atoi(cmd[0]);
	bola->posB.x=separar(cmd[2]);
	bola->posB.y=separar(cmd[3]);
	j1->posP.x=separar(cmd[4]);
	j1->posP.y=separar(cmd[5]);
	j2->posP.x=separar(cmd[6]);
	j2->posP.y=separar(cmd[7]);
	//printf("Bola X: %f, Bola Y: %f\n", bola->posB.x, bola->posB.y);
}

int GameState::separar( char pos[100])
{
	int k = strlen(pos);
	pos[k]=':';
	pos[k + 1] = '\0';
	
	char temp[4][20];
	char *pch;
	pch=strtok (pos,":");
	int j=0;
	while (pch != NULL && j<4)
	{
		strcpy(temp[j],pch);
		pch = strtok (NULL, ":");
		j++;
	}
	int value = atoi(temp[3]);
	return value;
}

char* GameState::toBuffer()
{
	return new char();
}

void GameState::update()
{
	
}
