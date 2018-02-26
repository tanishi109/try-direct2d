#pragma once

#include "Player.h"
#include "Screen.h"
#include "Scene.h"

class PlayerState
{
public:
    PlayerState();
    ~PlayerState();
    virtual void enter(Player& player);
    virtual PlayerState* update(Player& player, Screen& screen) = 0;
};
