#include "ball.h"
#include <stdlib.h>
#include <cstring>
#include <stdio.h>

ball::ball(int dirInicia, int w, int h)
{
	if(dirInicia == 0)
		dirB.set(2,0);
	else
		dirB.set(-2,0);
	posB.set(w/2,h/2);
}

void ball::mover(float deltaTime, int vel, Vector2D j1, Vector2D j2, int w, int h)
{
	//controle de colisão com Paletas dos jogadores
	if((posB.x <= j1.x+10 && posB.y+8>=j1.y && posB.y+2<=j1.y+120)||(posB.x+10>=j2.x && posB.y+8>=j2.y && posB.y+2<=j2.y+120))
	{
		dirB.x*=-1;
		if((posB.x <= j1.x+10 && posB.y+8>=j1.y && posB.y+10<=j1.y+20)||(posB.x+10>=j2.x && posB.y+8>=j2.y && posB.y+10<=j2.y+20))
			dirB.y=-2;
		if((posB.x <= j1.x+10 && posB.y>=j1.y+20 && posB.y+10<=j1.y+40)||(posB.x+10>=j2.x && posB.y>=j2.y+20 && posB.y+10<=j2.y+40))
			dirB.y=-1;
		if((posB.x <= j1.x+10 && posB.y>=j1.y+40 && posB.y+10<=j1.y+80)||(posB.x+10>=j2.x && posB.y>=j2.y+40 && posB.y+10<=j2.y+80))
			dirB.y=0;
		if((posB.x <= j1.x+10 && posB.y>=j1.y+80 && posB.y+10<=j1.y+100)||(posB.x+10>=j2.x && posB.y>=j2.y+80 && posB.y+10<=j2.y+100))
			dirB.y=1;
		if((posB.x <= j1.x+10 && posB.y>=j1.y+100 && posB.y+2<=j1.y+120)||(posB.x+10>=j2.x && posB.y>=j2.y+100 && posB.y+2<=j2.y+120))
			dirB.y=2;
	}

	//Verifica se bola bateu nas bordas superior e inferior
	if(posB.y<=10)
		dirB.y*=-1;
	if(posB.y+10>=h-10)
		dirB.y*=-1;
		
	posB += dirB*deltaTime*vel;
	//printf("Bola X: %f, Bola Y: %f\n", posB.x, posB.y);
}

char* ball::toChar() {
	char temp[512];
	sprintf(temp,"bola:posB:x:%d;bola:posB:y:%d;",(int)posB.x,(int)posB.y);
	return temp;
}
