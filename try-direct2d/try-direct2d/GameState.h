#pragma once

#include "SceneState.h"
#include "Player.h"
#include "Terrain.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    void enter();
    void update(Scene* scene);
private:
    Player* m_player;
    bool m_isFocus;

    void scroll();
    Terrain* checkCollision();
    void initPosition();
};

