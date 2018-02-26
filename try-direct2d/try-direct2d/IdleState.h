#pragma once

#include "PlayerState.h"
#include "Player.h"

class IdleState : public PlayerState
{
public:
    IdleState();
    ~IdleState();
    void update(Player& player, Screen& screen);
};
