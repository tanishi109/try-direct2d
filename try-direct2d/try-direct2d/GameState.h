#pragma once

#include "SceneState.h"
#include "Player.h"
#include "Terrain.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    virtual void enter();
    virtual SceneState* update();
private:
    Player* m_player;
    bool m_isFocus;

    void scroll();
    Terrain* checkCollision();
    void initPosition();
};

