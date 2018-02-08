#pragma once

#include "GameObject.h"

class Player : public GameObject
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void move(Screen* screen);
    void render(Screen * screen);
    std::tuple<int, int> getMainPinPos(); // FIXME: floatに統一したほうがいい
    std::tuple<float, float> getSubPinPosRotated();
    void setMainPinPos(int x, int y);
    void addChild();

    float m_degree;
    static const int m_collisionRadius = 3;
    Player* m_parent;
    Player* m_child;
private:
    int m_width;
    int m_height;
    int m_horizontalPinMargin;
};

