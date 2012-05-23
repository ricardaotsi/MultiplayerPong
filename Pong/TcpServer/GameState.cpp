#include "GameState.h"


GameState::GameState(int w, int h)
{
	// Inicia bola
	bola = new ball(rand()%2, w, h);
	// Inicia jogador 1
	j1 = new paddle(10, h/2-60);
	// Inicia jogador 2
	j2 = new paddle(w-20, h/2-60);
}


GameState::~GameState(void)
{
}

void GameState::fromBuffer()
{

}

char* GameState::toBuffer()
{
	char temp[256];
	char tempInt[3];
	strcpy( temp, "comando:inicia;");

	// Bola
	strcat( temp, bola->toChar() );

	return temp;
}

void GameState::update()
{
	
}
