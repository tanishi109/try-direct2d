#include "stdafx.h"
#include "Mathtool.h"


Mathtool::Mathtool()
{
}


Mathtool::~Mathtool()
{
}

float Mathtool::degToRad(float degree)
{
    return degree * M_PI / 180;
}

float Mathtool::radToDeg(float radian)
{
    return radian * 180 / M_PI;
}

float Mathtool::getDistance(float x1, float y1, float x2, float y2)
{
    return hypot(x2 - x1, y2 - y1);
}

float Mathtool::getRadFromPos(float x1, float y1, float x2, float y2)
{
    return std::atan2(y2 - y1, x2 - x1);
}
