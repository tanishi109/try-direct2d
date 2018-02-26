#pragma once

#include "Player.h"
#include "Screen.h"

class PlayerState
{
public:
    PlayerState();
    ~PlayerState();
    virtual void update(Player& player, Screen& screen) = 0;
};
