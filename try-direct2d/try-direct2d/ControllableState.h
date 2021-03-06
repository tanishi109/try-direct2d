#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Terrain.h"

class ControllableState : public PlayerState
{
public:
    ControllableState();
    ~ControllableState();
    void enter(Player& player);
    PlayerState* update(Player& player, Screen& screen);
private:
    // FIXME: player と screenを引数に取ることが多いのでPlayerStateのメンバ変数とかにしておきたい
    void scroll(Player& player, Screen& screen);
    Terrain* checkCollision(Player& player);
};
