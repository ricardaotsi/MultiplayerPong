#include "MathUtil.h"
#include "Vector2D.h"

using namespace math;

class ball
{
public:
	ball(int dirInicia, int w, int h);
	void mover(float deltaTime, int vel,Vector2D j1, Vector2D j2, int w, int h );
	Vector2D posB;
	Vector2D dirB;
	char* toChar();
};

