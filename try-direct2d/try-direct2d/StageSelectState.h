#pragma once

#include "SceneState.h"

class StageSelectState : public SceneState
{
public:
    StageSelectState();
    ~StageSelectState();
    void enter();
    void update(Scene* scene);
private:
    void loadTileMap();
};

