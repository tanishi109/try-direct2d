#pragma once

#include "SceneState.h"
#include "Player.h"
#include "Terrain.h"

class GameState : public SceneState
{
public:
    GameState();
    ~GameState();
    void enter(Scene& scene);
    void update(Scene* scene);
private:
    Player* m_player;
    void initPosition();
};

