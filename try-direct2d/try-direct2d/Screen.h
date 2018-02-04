#pragma once

class Screen
{
public:
    Screen();
    ~Screen();
    int m_x;
    int m_y;
    std::tuple<int, int> worldToScreen(int x, int y);
    std::tuple<int, int> screenToWorld(int x, int y);
};

