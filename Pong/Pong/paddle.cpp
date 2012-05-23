#include "paddle.h"


paddle::paddle(int x, int y)
{
	dirP.set(0,0);
	posP.set(x,y);
	ponto =0;
}


int paddle::mover(float deltaTime, int vel, int h, SDL_Event event)
{
	int i =0;
	if( event.type == SDL_KEYDOWN )
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
    }
	return i;
}