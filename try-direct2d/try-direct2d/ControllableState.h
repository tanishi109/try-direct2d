#pragma once

#include "PlayerState.h"
#include "Player.h"
#include "Terrain.h"

class ControllableState : public PlayerState
{
public:
    ControllableState();
    ~ControllableState();
    void update(Player& player, Screen& screen, Scene& scene);
private:
    // FIXME: player ‚Æ screen‚ğˆø”‚Éæ‚é‚±‚Æ‚ª‘½‚¢‚Ì‚ÅPlayerState‚Ìƒƒ“ƒo•Ï”‚Æ‚©‚É‚µ‚Ä‚¨‚«‚½‚¢
    void scroll(Player& player, Screen& screen);
    Terrain* checkCollision(Player& player);
};
