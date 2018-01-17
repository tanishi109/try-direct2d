#pragma once

#include <tuple>

class Player
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void render();
    std::tuple<int, int> getMainPinPos(); // FIXME: floatに統一したほうがいい
    std::tuple<float, float> getSubPinPosRotated();

    int m_x;
    int m_y;
    float m_degree;
private:
    int m_width;
    int m_height;
    int m_verticalPinMargin;
};

