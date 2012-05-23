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
	paddle( int x, int y);
	int mover(float deltaTime, int vel, int h,SDL_Event event);
};

