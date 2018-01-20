#include "stdafx.h"
#include "Collision.h"


Collision::Collision()
{
}


Collision::~Collision()
{
}

bool Collision::CheckCircleCollision(int x1, int y1, int r1, int x2, int y2, int r2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;
    int r =  r2 + r1;

    return ((dx * dx) + (dy * dy) < (r * r));
}
