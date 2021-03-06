#pragma once
#include "PlayerState.h"
#include "Player.h"

class MissedState : public PlayerState
{
public:
    MissedState();
    ~MissedState();
    PlayerState* update(Player& player, Screen& screen);
private:
    int m_stateTimer;
};
