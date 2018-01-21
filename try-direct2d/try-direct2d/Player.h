#pragma once

#include <tuple>

class Player
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void update();
    void move();
    void render();
    std::tuple<int, int> getMainPinPos(); // FIXME: float‚É“ˆê‚µ‚½‚Ù‚¤‚ª‚¢‚¢
    std::tuple<float, float> getSubPinPosRotated();
    void setMainPinPos(int x, int y);
    void setSubPinPos(int x, int y);
    void addChild();

    int m_x;
    int m_y;
    float m_degree;
    static const int m_collisionRadius = 3;
    Player* m_parent;
    Player* m_child;
private:
    int m_width;
    int m_height;
    int m_horizontalPinMargin;
};

