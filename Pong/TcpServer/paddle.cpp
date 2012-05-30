#include "paddle.h"


paddle::paddle(int x, int y)
{
	dirP.set(0,0);
	posP.set(x,y);
	ponto =0;
}


int paddle::mover(float deltaTime, int vel, int h, const char *direcao)
{
	int i =0;
	/*if( event.type == SDL_KEYDOWN )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP:
				dirP.set(0,-1);
				if(posP.y >= 0)
					posP+=dirP*deltaTime*vel;
				i=1;
				break;
            case SDLK_DOWN: 
				dirP.set(0,1);
				if(posP.y <= h- 120)
					posP+=dirP*deltaTime*vel;
				i=1;
				break;
		}	
    }*/
	if(strncmp("up",direcao,2)==0)
	{
		dirP.set(0,-1);
		if(posP.y >= 0)
			posP+=dirP*deltaTime*vel;
		i=1;
	}else{
		dirP.set(0,1);
		if(posP.y <= h- 120)
			posP+=dirP*deltaTime*vel;
		i=1;
	}
	return i;
}

char* paddle::toChar(char *nome)
{
	char tmp[512];
	sprintf(tmp,"%s:posP:x:%d;%s:posP:y:%d;",nome,(int)posP.x,nome,(int)posP.y);
	return tmp;
}