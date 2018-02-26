#pragma once

#include "GameObject.h"
#include "Scene.h"

class PlayerState;

class Player : public GameObject
{
public:
    Player(int x, int y, int w, int h);
    ~Player();
    void move(Screen* screen);
    void render(Screen* screen);
    std::tuple<int, int> getMainPinPos(); // FIXME: float‚É“ˆê‚µ‚½‚Ù‚¤‚ª‚¢‚¢
    std::tuple<float, float> getSubPinPosRotated();
    void setMainPinPos(int x, int y);
    void addChild();
    void update(Screen& screen);

    float m_degree;
    static const int m_collisionRadius = 3;
    Player* m_parent;
    Player* m_child;
    PlayerState* m_currentState;
    std::function<void(void)> m_onGoal;
private:
    int m_width;
    int m_height;
    int m_horizontalPinMargin;
};

