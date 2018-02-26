#pragma once
#include "PlayerState.h"
#include "Player.h"

class GoaledState : public PlayerState
{
public:
    GoaledState();
    ~GoaledState();
    PlayerState* update(Player& player, Screen& screen);
private:
    int m_stateTimer;
};
