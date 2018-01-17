#pragma once

#include "SceneState.h"
#include "Player.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    virtual void enter();
    virtual SceneState* update();
    virtual void onMouseMove();
private:
    Player* m_player;
};

