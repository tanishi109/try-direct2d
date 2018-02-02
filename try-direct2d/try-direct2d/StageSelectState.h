#pragma once

#include "SceneState.h"

class StageSelectState : public SceneState
{
public:
    StageSelectState();
    ~StageSelectState();
    virtual void enter();
    virtual SceneState* update();
private:
    void loadTileMap();
};

