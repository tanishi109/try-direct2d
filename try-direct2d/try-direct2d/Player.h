#pragma once

#include "GameObject.h"
#include <tuple>

class Player : public GameObject
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void update(Screen* screen);
    void move(Screen* screen);
    void render(Screen * screen);
    std::tuple<int, int> getMainPinPos(); // FIXME: float�ɓ��ꂵ���ق�������
    std::tuple<float, float> getSubPinPosRotated();
    void setMainPinPos(int x, int y);
    void setSubPinPos(int x, int y);
    void addChild();

    float m_degree;
    static const int m_collisionRadius = 3;
    Player* m_parent;
    Player* m_child;
    bool m_movable;
private:
    int m_width;
    int m_height;
    int m_horizontalPinMargin;
};

