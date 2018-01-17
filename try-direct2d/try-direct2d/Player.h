#pragma once

#include <tuple>

class Player
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void render();
    std::tuple<int, int> getMainPinPos();
private:
    int m_x;
    int m_y;
    int m_width;
    int m_height;
    float m_degree;
    int m_verticalPinMargin;
};

