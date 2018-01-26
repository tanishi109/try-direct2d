#include "stdafx.h"
#include "Screen.h"


Screen::Screen() :
m_x(0),
m_y(0)
{
}


Screen::~Screen()
{
}

std::tuple<int, int> Screen::WorldToScreen(int x, int y)
{
    return {x - m_x, y - m_y};
}

std::tuple<int, int> Screen::screenToWorld(int x, int y)
{
    return {x + m_x, y + m_y};
}
