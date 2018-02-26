#pragma once

#include "Player.h"
#include "Screen.h"
#include "Scene.h"

class PlayerState
{
public:
    PlayerState();
    ~PlayerState();
    virtual void update(Player& player, Screen& screen, Scene& scene) = 0;
};
