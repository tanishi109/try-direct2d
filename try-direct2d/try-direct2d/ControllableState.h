#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Terrain.h"

class ControllableState : public PlayerState
{
public:
    ControllableState();
    ~ControllableState();
    void update(Player& player, Screen& screen);
private:
    // FIXME: player �� screen�������Ɏ�邱�Ƃ������̂�PlayerState�̃����o�ϐ��Ƃ��ɂ��Ă�������
    void scroll(Player& player, Screen& screen);
    Terrain* checkCollision(Player& player);
};
