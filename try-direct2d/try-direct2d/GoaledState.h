#pragma once
#include "PlayerState.h"
#include "Player.h"

class GoaledState : public PlayerState
{
public:
    GoaledState();
    ~GoaledState();
    void update(Player& player, Screen& screen, Scene& scene);
private:
    int m_stateTimer;
};
