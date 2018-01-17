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
