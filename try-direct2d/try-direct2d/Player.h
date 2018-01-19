#pragma once

#include <tuple>

class Player
{
public:
    Player(int x, int y, int w, int h, int childrenCount);
    ~Player();
    void update();
    void render();
    std::tuple<int, int> getMainPinPos(); // FIXME: float‚É“ˆê‚µ‚½‚Ù‚¤‚ª‚¢‚¢
    std::tuple<float, float> getSubPinPosRotated();
    void setMainPinPos(int x, int y);
    void setSubPinPos(int x, int y);

    int m_x;
    int m_y;
    float m_degree;
private:
    int m_width;
    int m_height;
    int m_horizontalPinMargin;
    const int m_childrenCount;
    Player* m_children[];

    void updateForChild(Player* parent);
};

