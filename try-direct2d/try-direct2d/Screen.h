#pragma once

#include <tuple>

class Screen
{
public:
    Screen();
    ~Screen();
    int m_x;
    int m_y;
    std::tuple<int, int> WorldToScreen(int x, int y);
    std::tuple<int, int> ScreenToWorld(int x, int y);
};

