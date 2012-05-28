#ifndef __PADDLE_H__
#define __PADDLE_H__

#include "MathUtil.h"
#include "Vector2D.h"
#include <SDL\SDL.h>

using namespace math;

class paddle
{

public:
	Vector2D posP;
	Vector2D dirP;
	int ponto;
	//paddle( int x, int y);
	paddle();
	int mover(float deltaTime, int vel, int h,SDL_Event event);
};

#endif
