#pragma once

#include "PlayerState.h"
#include "Player.h"

class IdleState : public PlayerState
{
public:
    IdleState();
    ~IdleState();
    PlayerState* update(Player& player, Screen& screen);
};
